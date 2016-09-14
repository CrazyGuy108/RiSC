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
		std::vector<std::vector<char*>> words;
		size_t wordIndex{ 0 };
		size_t lineIndex{ 0 };
		bool foundSpace{ false };
		char* temp;
		/***** test this stuff to see if it works *****/
		for (size_t index{ 0 }; contents[index] != '\0' && index < SIZE_MAX; ++index)
		{
			switch (contents[index])
			{
			case ' ':
			case '\t': // new word
				if (foundSpace)
					break;

				foundSpace = true; // ignore spaces/tabs until next nonspecial character

				if (contents[index - 1] == ':') // add to symbol table
				{
					
				}
				else // add to words list
				{
					contents[index] = '\0'; // terminate with a null character where the tab/space was found
					words[lineIndex].push_back(contents); // pointer to first nonspecial character
				}

				// reset and increment word index
				contents += index;
				index = 0;
				++wordIndex;
				break;

			case '\n': // new line
				words.push_back(std::vector<char*>{}); // construct empty vector

				// reset and increment line index
				contents += index;
				wordIndex = 0;
				++lineIndex;
				break;

			case '#': // ignore until new line
				temp = strchr(contents + index, '\n');
				if (temp == nullptr)
					goto read_end; // newline not found, so must be end of file
				else
					contents = temp - 1; // the next loop will execute the code associated with newlines
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
	}
	else
		; // error: no dest file specified
}