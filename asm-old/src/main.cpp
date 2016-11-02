#include "../include/assembler.hpp"

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream ifile;
		std::ofstream ofile;

		const char* ext{ strrchr(argv[1], '.') };

		if (ext && !strcmp(ext, ".asm"))
		{
			ifile.open(argv[1]);
			if (ifile.fail())
			{
				std::cout << "error: input file failed to open\n";
				return 0;
			}
		}

		ext = strrchr(argv[2], '.');

		if (ext && !strcmp(ext, ".risc"))
		{
			ofile.open(argv[2], std::ofstream::binary);
			if (ofile.fail())
			{
				std::cout << "error: output file failed to open\n";
				return 0;
			}
		}

		assemble(ifile, ofile);

		ifile.close();
		ofile.close();
	}

	return 0;
}
