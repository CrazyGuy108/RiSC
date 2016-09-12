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
				words[lineIndex].push_back(contents); // pointer to last nonspecial character
				contents[index] = '\0';				  // terminate string with a null character where the tab/space was found

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
				char* temp{ strchr(contents + index, '\n') };
				if (temp == nullptr)
					goto read_end;   // newline not found, so must be end of file
				contents = temp - 1; // the next loop will execute the code associated with newlines
				break;
			}
		}
		read_end:
		
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