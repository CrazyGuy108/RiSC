#include "instruction.h"

Line::Line(uint16_t* instructions, size_t length)
	: instructions{ instructions }, length{ length } {}

/***** move to utilities and rename instruction to line? *****/
Line compile(size_t argc, const char** argv)
{
	if (argc > 0)
	{
		int index{ opcodes.search(argv[0]) };
		if (index != -1)
		{
			return opcodes[index].value(argc, argv);
		}
		else
		{
			index = pseudos.search(argv[0]);
			if (index != -1)
			{
				return pseudos[index].value(argc, argv);
			}
			else
				; // error: undefined opcode
		}
	}
	else
		return Line{ nullptr, 0 }; // disregard as a blank line
}