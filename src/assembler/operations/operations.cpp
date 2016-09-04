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

		return Line{ new RRR[1]{ RRR{ ADD, regs[operands[0]], regs[operands[1]], regs[operands[2]] } }, 1 };
	}
	else
		; // error: operand count does not match
}

Line addi(size_t argc, const char** argv)
{
	if (argc == 4)
	{
		int operands[2]
		{
			regs.search(argv[1]),
			regs.search(argv[2])
		};

		for (uint8_t i{ 0 }; i < 2; ++i)
		{
			if (operands[i] < 0)
				; // error: undefined operand
		}

		uint16_t immed{ imm(argv[3]) };

		if (immed & IMM7_MASK == immed || immed & IMM7_NEG_MASK == IMM7_NEG_MASK)
			return Line{ new RRI[1]{ RRI{ ADDI, regs[operands[0]], regs[operands[1]], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line nand(size_t argc, const char** argv)
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

		return Line{ new RRR[1]{ RRR{ NAND, regs[operands[0]], regs[operands[1]], regs[operands[2]] } }, 1 };
	}
	else
		; // error: operand count does not match
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