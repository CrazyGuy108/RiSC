#include "../include/emulator.h"

void emulator(std::ifstream& ifile)
{
	uint16_t* contents;
	size_t length;

	// get length of file
	ifile.seekg(0, std::ifstream::end);
	length = ifile.tellg();
	ifile.seekg(0, std::ifstream::beg);

	// copy file
	contents = new uint16_t[length / sizeof(char)];
	ifile.read((char*)contents, length);
}
