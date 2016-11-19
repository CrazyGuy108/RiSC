#include <fstream>  // for ifstream
#include <iostream> // for cout
#include "../include/emulator.hpp"

#define TEST

#ifdef TEST
#define IF_TEST(...) __VA_ARGS__
#else
#define IF_TEST(...)
#endif

int main(int argc, char** argv)
{
	IF_TEST
	(
		argc = 2;
		argv = new char*[2];
		argv[1] = "test.risc";
	)
	if (argc == 2)
	{
		const char* ext{ strrchr(argv[1], '.') };
		if (ext && !strcmp(ext, ".risc"))
		{
			std::ifstream ifile{ argv[1], std::ifstream::binary };
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
				ifile.close();

				emulator(contents, length);

				delete[] contents;
			}
			else
				std::cout << "error: input file failed to open\n";
		}
		else
			std::cout << "error: invalid file extension\n";
	}
	else
		std::cout << "error: input file not specified\n";
	IF_TEST(delete[] argv);

	return 0;
}
