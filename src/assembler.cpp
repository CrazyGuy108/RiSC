#include "../include/assembler.h"

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
		char* contents = new char[length + 1];
		infile.read(contents, length);
		contents[length] = '\0'; // null character to prevent reading garbage data

		// no need to read from it anymore
		infile.close();

		/***** PASS ONE: preprocessor *****/

		static const Table<Opcode> ops
		{
			{ "add",{ &add,  1 } },
			{ "addi",{ &addi, 1 } },
			{ "beq",{ &beq,  1 } },
			{ "halt",{ &halt, 1 } },
			{ "jalr",{ &jalr, 1 } },
			{ "lli",{ &lli,  1 } },
			{ "lui",{ &lui,  1 } },
			{ "lw",{ &lw,   1 } },
			{ "movi",{ &movi, 2 } },
			{ "nand",{ &nand, 1 } },
			{ "nop",{ &nop,  1 } },
			{ "sw",{ &sw,   1 } }
		};

		std::vector<std::vector<char*>> words{ std::vector<char*>{} };
		std::vector<OP((*))> opcodes;
		char* iterator{ contents };
		size_t charIndex{ 0 };
		size_t wordIndex{ 0 };
		size_t lineIndex{ 0 };
		bool foundSpace{ true };
		inst_t lineAddr{ 0 };

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
					Opcode opcode{ ops[words[lineIndex][0]] }; // temp storage for Opcode object
					opcodes.push_back(opcode.getFunc());
					words.push_back(std::vector<char*>{});

					foundSpace = true; // allows spaces/tabs before the first word of the next line
					++lineIndex;
					lineAddr += opcode.length();
				}

				// reset line
				wordIndex = 0;
				iterator += charIndex + 1; // sets iterator to just after the newline
				charIndex = 0;
				break;

			case '\t': // new word/label
			case ' ':
				// skip multiple spaces/tabs
				if (foundSpace)
				{
					iterator += charIndex + 1; // sets iterator to just after the space
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
						symbols.insert(iterator, lineAddr);
					}
					catch (SymbolException e)
					{
						std::cout << "error in line " << lineIndex << ": redefinition of label \"" << e.what() << "\"\n";
					}
				}
				else
					words[lineIndex].push_back(iterator);

				// reset word
				++wordIndex;
				iterator += charIndex + 1;
				charIndex = 0;
				break;

			default: // nonspecial character
				foundSpace = false;
				++charIndex;
			}
		}

		unsigned int errors{ 0 };

		// resolve labels and clean up the code
		/*
		for (uint16_t i{ 0 }; i < words.size(); ++i)
		{
			if (words[i].empty()) // blank line should be removed
				words.erase(words.begin() + i--);
			else // check if label
			{
				size_t len{ 0 };

				while (words[i][0][len] != '\0')
					++len;

				if (words[i][0][len - 1] == ':') // check last character
				{
					try
					{
						words[i][0][len - 1] = '\0'; // overwrite colon with null character
						symbols.insert(words[i][0], i); // the value in this case would be i, the current line number
					}
					catch (SymbolException e)
					{
						std::cout << "error in line " << i << ": redefinition of label \"" << e.what() << "\"\n";
						++errors;
					}

					words[i].erase(words[i].begin()); // remove first word because it's a label
				}
			}
		}*/

		// compile into bytecode
		/*
		line_t bytecode;
		line_t tmp;
		size_t line{ 0 };
		
		for (size_t i{ 0 }; i < words.size(); ++i)
		{
			std::cout << "compiling line " << i << "...\n";

			try
			{
				tmp = compile(words[i].size(), words[i].data(), line);
				bytecode.insert(bytecode.end(), tmp.begin(), tmp.end());
				line += tmp.size(); // some instructions take multiple instruction words when compiled
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
		}*/

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