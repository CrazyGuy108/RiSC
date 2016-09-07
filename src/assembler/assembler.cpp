#include "assembler.h"

void assemble(int argc, char** argv)
{
	std::ifstream infile{ argv[1] };

	// get file length
	infile.seekg(0, infile.end);
	std::streamsize length = infile.tellg();
	infile.seekg(0, infile.beg);

	// put into char array
	char* contents = new char[length];
	infile.read(contents, length);

	infile.close();
}