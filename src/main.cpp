#include "../include/assembler.h"

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream ifile;
		std::ofstream ofile;
		const char* ext{ strrchr(argv[1], '.') };

		if (!strcmp(ext, ".asm"))
			ifile.open(argv[1]);

		ext = strrchr(argv[2], '.');

		if(!strcmp(ext, ".risc"))
			ofile.open(argv[2], std::ios::binary);

		if (ifile.fail())
			std::cout << "error: input file failed to open\n";
		else if (ofile.fail())
			std::cout << "error: output file failed to open\n";
		else
		{
			assemble(ifile, ofile);

			ifile.close();
			ofile.close();
		}
	}

	return 0;
}
