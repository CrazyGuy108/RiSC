#include "assembler.h"

void assemble(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream infile{ argv[1] };

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

		// build symbol table
		
		// compile into bytecode
		
		// write to file
		std::ofstream outfile{ argv[2] };

		outfile.close();
	}
	else
		; // error: no dest file specified
}