#include "assembler/assembler.h"

/***** move some stuff to a global utilities folder *****/
typedef void(*extension_t)(int argc, char** argv);

Table<extension_t> extensions
{
	{ ".asm", &assemble }
};

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		// get file extension

		const char* extension{ strchr(argv[1], '/') };

		if (extension == nullptr)
			extension = strchr(argv[1], '.');
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