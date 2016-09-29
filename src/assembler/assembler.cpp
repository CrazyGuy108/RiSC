#include "assembler.h"

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

		// split into words and ignore comments
		char* iterator{ contents };
		std::vector<std::vector<char*>> words{ std::vector<char*>{} };
		size_t wordIndex{ 0 };
		uint16_t lineIndex{ 0 };
		bool foundSpace{ false };
		size_t index{ 0 };
		while (iterator[index] != '\0')
		{
			switch (iterator[index])
			{
			case '#': // comment
				// ignore everything until newline
				while (iterator[index] != '\n')
					++index;
				// next case will obviously be a newline so don't break

			case '\n': // new line
				words.push_back(std::vector<char*>{}); // construct new line

				// reset line
				++lineIndex;
				wordIndex = 0;
				iterator += index + 1; // sets iterator to just after the newline
				index = 0;
				break;

			case '\t': // new word/label
			case ' ':
				// skip multiple spaces/tabs
				if (foundSpace)
					break;

				foundSpace = true;

				words[lineIndex].push_back(iterator); // iterator holds base pointer of string
				iterator[index] = '\0'; // terminate the new substring

				// reset word
				++wordIndex;
				iterator += index + 1;
				index = 0;
				break;

			default: // nonspecial character
				foundSpace = false;
				++index;
			}
		}

		// resolve labels and clean up the code
		
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
					words[i].erase(words[i].begin()); // remove first word because it's a label

					symbols.insert(words[i][0], i); // the value in this case would be i, the current line number
					words[i][0][len - 1] = '\0'; // overwrite colon with null character
				}
			}
		}

		// compile into bytecode

		for (uint16_t i{ 0 }; i < words.size(); ++i)
		{
			compile(words[i].size(), (const char**)(words[i].data()), i); // placeholder
		}

		/*
		// write to file
		std::ofstream outfile{ argv[2] };

		if (outfile.fail())
			return; // error: file open failed

		outfile.close();
		*/
		
		

		// iterate through lines
		for (size_t i{ 0 }; i < words.size(); ++i)
		{
			// iterator through words
			for (size_t j{ 0 }; j < words[i].size(); ++j)
			{
				std::cout << words[i][j] << ",";
			}
			std::cout << '\n';
		}

		// iterate through symbols
		for (size_t i{ 0 }; i < symbols.size(); ++i)
		{
			std::cout << symbols[i] << '\n';
		}

		delete contents;
	}
	else
		; // error: no dest file specified
}