#include "instruction.h"

Line::Line(uint16_t* instructions, size_t length)
	: instructions{ instructions }, length{ length } {}

Line compile(size_t argc, const char** argv)
{
	if (argc > 0)
	{
		int index{ opcodes.search(argv[0]) };
		// call appropriate function
		// i.e. return add(argc, argv);
	}
	else
		return Line{ nullptr, 0 }; // disregard as a blank line
}