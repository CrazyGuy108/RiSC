#include "instruction.h"

Line::Line(uint16_t* instructions, size_t length)
	: instructions{ instructions }, length{ length } {}

Line::~Line()
{
	if (instructions != nullptr)
		delete[] instructions;
}

/***** move to utilities and rename instruction to line? *****/
Line compile(size_t argc, const char** argv)
{
	if (argc > 0)
	{
		int index{ ops.search(argv[0]) };
		if (index != -1)
		{
			return ops[index].value(argc, argv);
		}
		else
			; // error: undefined opcode
	}
	else
		return Line{ nullptr, 0 }; // disregard as a blank line
}