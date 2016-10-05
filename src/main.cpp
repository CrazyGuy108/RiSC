#include "../include/assembler.h"

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		std::ifstream ifile{ argv[1] };
		std::ofstream ofile{ argv[2], std::ios::binary };

		if (ifile.fail())
			std::cout << "error: input file failed to open\n";
		else if (ofile.fail())
			std::cout << "error: output file failed to open\n";
		else
			assemble(ifile, ofile);
	}

	return 0;
}
