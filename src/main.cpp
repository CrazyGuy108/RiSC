#include "../include/assembler.h"

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream ifile;
		std::ofstream ofile;
		const char* iname{ strrchr(argv[1], '.') };
		const char* oname{ strrchr(argv[2], '.') };

		if (!strcmp(iname, ".asm"))
			ifile.open(iname);
		if(!strcmp(oname, ".risc"))
			ofile.open(oname, std::ios::binary);

		if (ifile.fail())
			std::cout << "error: input file failed to open\n";
		else if (ofile.fail())
			std::cout << "error: output file failed to open\n";
		else
			assemble(ifile, ofile);
	}

	return 0;
}
