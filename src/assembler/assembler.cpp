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
		std::streamsize length = infile.tellg();
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
		bool foundComment{ false };
		/***** test this stuff to see if it works *****/
		for (size_t index{ 0 }; iterator[index] != '\0' && index < SIZE_MAX; ++index)
		{
			switch (iterator[index])
			{
			case '\n': // new line
				words.push_back(std::vector<char*>{}); // construct empty vector

				// reset and increment line index
				wordIndex = 0;
				++lineIndex;

				// check if the end of a comment
				if (foundComment)
				{
					foundComment = false;
					iterator += index;
					index = 0;
					break;
				}

				// process new word
			case ' ':
			case '\t': // new word
				if (foundSpace || foundComment) // skip multiple spaces or a comment
					break;

				foundSpace = true; // ignore spaces/tabs until next nonspecial character

				if (iterator[index - 1] == ':') // add to symbol table
				{
					iterator[index - 1] = '\0'; // terminate with null character where the colon was found
					symbols.insert(++iterator, lineIndex); // the +1 takes out the newline
				}
				else // add to words list
				{
					iterator[index] = '\0'; // terminate with null character where the tab/space was found
					words[lineIndex].push_back(iterator); // pointer to first nonspecial character
				}

				// reset and increment word index
				iterator += index;
				index = 0;
				++wordIndex;
				break;

			case '#': // ignore until new line
				foundComment = true;
				break;
				
			default:
				foundSpace = false; // nonspecial character found
			}
		}
		
		// compile into bytecode
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

		delete contents;
	}
	else
		; // error: no dest file specified
}