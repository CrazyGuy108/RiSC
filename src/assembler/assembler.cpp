#include "assembler.h"

void assemble(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream infile{ argv[1] };

		if (infile.fail())
			return; // error: file open failed

		// get file length
		infile.seekg(0, infile.end);
		std::streamsize length = infile.tellg();
		infile.seekg(0, infile.beg);

		// put into char array
		char* contents = new char[length];
		infile.read(contents, length);

		// no need to read from it anymore
		infile.close();

		// split into words and ignore comments
		char* iterator{ contents };
		std::vector<std::vector<char*>> words;
		size_t wordIndex{ 0 };
		size_t lineIndex{ 0 };
		bool foundSpace{ false };
		char* temp;
		/***** test this stuff to see if it works *****/
		for (size_t index{ 0 }; iterator[index] != '\0' && index < SIZE_MAX; ++index)
		{
			switch (iterator[index])
			{
			case ' ':
			case '\t': // new word
				if (foundSpace)
					break;

				foundSpace = true; // ignore spaces/tabs until next nonspecial character

				if (iterator[index - 1] == ':') // add to symbol table
				{
					iterator[index - 1] = '\0'; // terminate with null character where the colon was found
					// insert word and lineIndex to symbol table
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

			case '\n': // new line
				words.push_back(std::vector<char*>{}); // construct empty vector

				// reset and increment line index
				iterator += index;
				wordIndex = 0;
				++lineIndex;
				break;

			case '#': // ignore until new line
				temp = strchr(iterator + index, '\n');
				if (temp == nullptr)
					goto read_end; // newline not found, so must be end of file
				else
					iterator = temp - 1; // the next loop will execute the code associated with newlines
				break;
				
			default:
				foundSpace = false; // nonspecial character found
			}
		}
		read_end:
		
		// compile into bytecode
		/*
		// write to file
		std::ofstream outfile{ argv[2] };

		if (outfile.fail())
			return; // error: file open failed

		outfile.close();
		*/

		delete contents;
	}
	else
		; // error: no dest file specified
}