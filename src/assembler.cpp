#include "../include/assembler.h"

size_t preprocess(std::vector<std::vector<char*>>& words, std::vector<Opcode>& opcodes, char* iterator)
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
	inst_t lineAddr{ 0 };
	size_t errors{ 0 };

	while (iterator[charIndex] != '\0')
	{
		switch (iterator[charIndex])
		{
		case '#': // comment
			// ignore everything until newline
			while (iterator[charIndex] != '\n')
				++charIndex;

			// next case will obviously be a newline so don't break

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
			}

			// reset line
			wordIndex = 0;
			iterator = &iterator[charIndex + 1]; // sets iterator to just after the newline
			charIndex = 0;
			break;

		case '\t': // new word/label
		case ' ':
			// skip multiple spaces/tabs
			if (foundSpace)
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

	return errors;
}

size_t compile(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes)
{
	size_t errors{ 0 };
	line_t bytecode;
	line_t tmp;
	size_t line{ 0 };

	for (size_t i{ 0 }; i < words.size(); ++i)
	{
		std::cout << "compiling line " << i << "...\n";

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

	return errors;
}

void assemble(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream infile{ argv[1] };
		
		if (!infile.is_open()) // failed to open
		{
			std::cout << "error: input file failed to open\n";
			return;
		}

		std::cout << "input file opened\n";

		// get file length
		infile.seekg(0, infile.end);
		size_t length{ (size_t)infile.tellg() };
		infile.seekg(0, infile.beg);

		// put into char array
		char* contents = new char[length];
		infile.read(contents, length - 1);
		contents[length - 1] = '\0'; // null character to prevent reading garbage data

		// no need to read from it anymore
		infile.close();

		// setup

		std::vector<std::vector<char*>> words{ std::vector<char*>{} }; // [lines][words] vector for parsing
		std::vector<Opcode> opcodes; // array of opcode functions to be called
		size_t errors; // keeps track of how many errors there are

		// 2 passes

		errors =  preprocess(words, opcodes, contents);
		errors += compile(words, opcodes);

		/*
		// write to file
		if(errors)
			std::cout << "exited with " << errors << " errors\n";
		else
		{
			std::ofstream outfile{ argv[2] };
			
			if (outfile.fail())
			return; // error: file open failed
			
			outfile.close();
		}
		
		*/
		
		// test
		/*
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

		std::cout << "\n";*/
		
		delete[] contents;
	}
	else
		; // error: no dest file specified
}