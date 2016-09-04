#include <fstream>
#include "assembler/assembler.h"

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		std::ifstream source{ argv[2] };
		
		// verify extension

		const char* extension{ strchr(argv[2], '/') };

		if (extension == nullptr)
			extension = strchr(argv[2], '.');
		else
			extension = strchr(extension, '.');

		if (strcmp(extension, ".asm") == 0)
		{
			// assemble
		}
		else
			; // error: invalid extension

		source.close();
	}
	else
		; // error: no file
	
	return 0;
}