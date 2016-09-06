#include "assembler.h"

void assemble(int argc, char** argv)
{
	std::ifstream infile{ argv[1] };

	// get file length
	infile.seekg(0, infile.end);
	std::streamoff length = infile.tellg();
	infile.seekg(0, infile.beg);

	infile.close();
}