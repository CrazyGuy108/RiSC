#include <fstream>  // for ifstream
#include <iostream> // for cout
#include "../include/emulator.h"

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		const char* ext{ strrchr(argv[1], '.') };
		if (ext && !strcmp(ext, ".risc"))
		{
			std::ifstream ifile{ argv[1] };
			if (ifile.is_open())
			{
				char* contents;
				size_t length;

				// get length of file
				ifile.seekg(0, std::ifstream::end);
				length = ifile.tellg();
				ifile.seekg(0, std::ifstream::beg);

				// copy file
				contents = new char[length];
				ifile.read(contents, length);

				emulator(contents, length);
			}
			else
				std::cout << "error: input file failed to open\n";
		}
		else
			std::cout << "error: invalid file extension\n";
	}
	else
		std::cout << "error: input file not specified\n";

	return 0;
}
