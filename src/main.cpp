#include "../include/assembler.h"

/***** move some stuff to a global utilities folder *****/
typedef void(*extension_t)(int argc, char** argv);

Table<extension_t> extensions
{
	{ ".asm", &assemble }
};

int main(int argc, char** argv)
{
	// test
	argc = 3;
	argv = new char*[3];
	argv[1] = "test.asm";

	if (argc >= 2)
		extensions[".asm"](argc, argv);
	else
		; // error: no file

	return 0;
}