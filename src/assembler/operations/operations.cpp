#include "operations.h"

Line add(size_t argc, const char** argv)
{
	if (argc == 4)
	{
		int operands[3]
		{
			regs.search(argv[1]),
			regs.search(argv[2]),
			regs.search(argv[3])
		};

		for (uint8_t i{ 0 }; i < 3; ++i)
		{
			if (operands[i] < 0)
				; // error: undefined operand
		}

		return Line{ new uint16_t[1]{ ADD | (regs[operands[0]].value << 13) | (regs[operands[0]].value << 10) | (regs[operands[0]].value) }, 1 };
	}
	else
		; // error: operand count does not match
}

Line addi(size_t argc, const char** argv)
{

}

Line nand(size_t argc, const char** argv)
{

}

Line lui(size_t argc, const char** argv)
{

}

Line sw(size_t argc, const char** argv)
{

}

Line lw(size_t argc, const char** argv)
{

}

Line beq(size_t argc, const char** argv)
{

}

Line jalr(size_t argc, const char** argv)
{

}

Line nop(size_t argc, const char** argv)
{

}

Line halt(size_t argc, const char** argv)
{

}

Line lli(size_t argc, const char** argv)
{

}

Line movi(size_t argc, const char** argv)
{

}

Line fill(size_t argc, const char** argv)
{

}

Line space(size_t argc, const char** argv)
{

}