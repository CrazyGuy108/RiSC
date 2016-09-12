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
		/***** test this stuff to see if it works *****/
		for (size_t index{ 0 }; contents[index] != '\0' && index < SIZE_MAX; ++index)
		{
			switch (contents[index])
			{
			case ' ':
			case '\t': // new word
				words[lineIndex].push_back(contents);
				contents[index] = '\0';

				// reset and increment word index
				contents += index;
				index = 0;
				++wordIndex;
				break;

			case '\n': // new line
				words.push_back(std::vector<char*>{});

				// reset and increment line index
				contents += index;
				wordIndex = 0;
				++lineIndex;
				break;

			case '#': // ignore until new line
				
				break;
			}
		}
		
		// build symbol table
		
		// compile into bytecode
		
		// write to file
		std::ofstream outfile{ argv[2] };

		if (outfile.fail())
			return; // error: file open failed

		outfile.close();
	}
	else
		; // error: no dest file specified
}