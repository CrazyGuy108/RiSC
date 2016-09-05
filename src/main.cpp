#include <fstream>
#include "assembler/assembler.h"

Table<void(*)(int argc, char** argv)> extensions
{
	{ ".asm", &assemble },
	{ ".s", &assemble }
};

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		// get file extension

		const char* extension{ strchr(argv[2], '/') };

		if (extension == nullptr)
			extension = strchr(argv[2], '.');
		else
			extension = strchr(extension, '.');

		// verify extension

		int index{ extensions.search(extension) };

		if (index >= 0)
			extensions[index](argc, argv);
		else
			; // error: invalid extension
	}
	else
		; // error: no file
	
	return 0;
}