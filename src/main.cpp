#include "../include/assembler.h"

int main(int argc, char** argv)
{

	if (argc >= 2)
		assemble(argc, argv);
	else
		; // error: no file

	return 0;
}