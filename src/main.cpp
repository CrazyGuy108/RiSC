#include <fstream>
#include "assembler/assembler.h"

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		std::ifstream source{ argv[2] };
		
		source.close();
	}
	else
		; // error: no file
	
	return 0;
}