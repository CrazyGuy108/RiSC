#include "../include/assembler.hpp"

size_t preprocessor(std::vector<std::vector<char*>>& words, std::vector<Opcode>& opcodes, char* iterator)
{
	static const Table<Opcode> ops
	{
		{ "add",  { &add,  1 } },
		{ "addi", { &addi, 1 } },
		{ "beq",  { &beq,  1 } },
		{ "halt", { &halt, 1 } },
		{ "jalr", { &jalr, 1 } },
		{ "lli",  { &lli,  1 } },
		{ "lui",  { &lui,  1 } },
		{ "lw",   { &lw,   1 } },
		{ "movi", { &movi, 2 } },
		{ "nand", { &nand, 1 } },
		{ "nop",  { &nop,  1 } },
		{ "sw",   { &sw,   1 } }
	};

	size_t charIndex{ 0 };
	size_t wordIndex{ 0 };
	size_t lineIndex{ 0 };
	bool foundSpace{ true };
	bool foundComment{ false };
	inst_t lineAddr{ 0 };
	size_t errors{ 0 };

#ifdef DEBUG
	std::cout << "preprocessing line 0...\n";
#endif

	while (iterator[charIndex] != '\0')
	{
		switch (iterator[charIndex])
		{
		case '#': // comment
			foundComment = true;
			break;

		case '\n': // new line
			// parse/cleanup line
			if (words[lineIndex].empty()) // blank lines should be removed
				words.erase(words.begin() + lineIndex);
			else
			{
				try
				{
					opcodes.push_back(ops[words[lineIndex][0]]);
					lineAddr += opcodes[lineIndex].length();
				}
				catch (TokenException e)
				{
					std::cout << "error in line " << lineIndex << ": undefined opcode \"" << e.what() << "\"\n";
					++errors;
				}

				words.push_back(std::vector<char*>{});
				++lineIndex;
				foundSpace = true; // allows spaces/tabs before the first word of the next line

#ifdef DEBUG
				std::cout << "preprocessing line " << lineIndex << "...\n";
#endif

			}

			// reset line
			foundComment = false;
			wordIndex = 0;
			iterator = &iterator[charIndex + 1]; // sets iterator to just after the newline
			charIndex = 0;
			break;

		case '\t': // new word/label
		case ' ':
			// skip multiple spaces/tabs
			if (foundSpace || foundComment)
			{
				iterator = &iterator[charIndex + 1]; // sets iterator to just after the space
				charIndex = 0;
				break;
			}

			foundSpace = true;

			iterator[charIndex] = '\0'; // terminate the new substring

			// add to words vector or symbol table
			if (iterator[charIndex - 1] == ':')
			{
				try
				{
					iterator[charIndex - 1] = '\0'; // remove the colon
					symbols.insert(iterator, lineAddr);
				}
				catch (SymbolException e)
				{
					std::cout << "error in line " << lineIndex << ": redefinition of label \"" << e.what() << "\"\n";
					++errors;
				}
			}
			else
				words[lineIndex].push_back(iterator);

			// reset word
			++wordIndex;
			iterator = &iterator[charIndex + 1];
			charIndex = 0;
			break;

		default: // nonspecial character
			foundSpace = false;
			++charIndex;
		}
	}

	words.pop_back(); // close last line (should be a blank/commented line)

	return errors;
}

size_t compiler(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes, line_t& bytecode)
{
	size_t errors{ 0 };
	line_t tmp;
	size_t line{ 0 };

	for (size_t i{ 0 }; i < words.size(); ++i)
	{

#ifdef DEBUG

		std::cout << "compiling line " << i << "...\n";

#endif

		try
		{
			tmp = opcodes[i].getFunc()(words[i].size(), (const char**)words[i].data(), line);
			bytecode.insert(bytecode.end(), tmp.begin(), tmp.end());
			line += opcodes[i].length(); // some instructions take multiple instruction words when compiled
		}
		catch (TokenException e)
		{
			std::cout << "error in line " << i << ": unresolved symbol \"" << e.what() << "\"\n";
			++line;
			++errors;
		}
		catch (OperandException e)
		{
			std::cout << "error in line " << i << ": opcode \"" << e.what() << "\" expected " << e.getExpected() << " operands but was given " << e.getGiven() << " instead\n";
			++line;
			++errors;
		}

	}

#ifdef DEBUG

	std::cout << "\nsource:\n";

	// iterate through lines
	for (size_t i{ 0 }; i < words.size(); ++i)
	{
		// iterator through words
		for (size_t j{ 0 }; j < words[i].size(); ++j)
		{
			std::cout << words[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << "\nlabels:\n";

	// iterate through labels
	for (const auto& i : symbols)
		std::cout << i.first << ": " << i.second << "\n";

	std::cout << "\nbytecode:\n";

	// iterate through bytecode
	for (size_t i{ 0 }; i < bytecode.size(); ++i)
		std::cout << std::hex << bytecode[i] << '\n';

	std::cout << "\n";

#endif // DEBUG

	return errors;
}

void assemble(std::ifstream& ifile, std::ostream& ofile)
{
		// get file length
		ifile.seekg(0, ifile.end);
		size_t length{ (size_t)ifile.tellg() };
		ifile.seekg(0, ifile.beg);

		// put into char array
		char* contents = new char[length];
		ifile.read(contents, length - 1);
		contents[length - 1] = '\0'; // null character to prevent reading garbage data

		// setup

		std::vector<std::vector<char*>> words{ std::vector<char*>{} }; // [lines][words] vector for parsing
		std::vector<Opcode> opcodes; // array of opcode functions to be called
		line_t bytecode; // array containing the bytecode
		size_t errors; // keeps track of how many errors there are

		// 2 passes

		errors =  preprocessor(words, opcodes, contents);
		errors += compiler(words, opcodes, bytecode);

#ifndef DEBUG

		// write to file

		if(errors)
			std::cout << "exited with " << errors << " errors\n";
		else
		{
			for (size_t i{ 0 }; i < bytecode.size(); ++i)
				ofile.write(reinterpret_cast<const char*>(&bytecode[i]), sizeof(inst_t));
		}

#endif // DEBUG
		
		delete[] contents;
}
