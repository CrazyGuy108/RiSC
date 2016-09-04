#include "operations.h"

Line add(size_t argc, const char** argv)
{
	if (argc == 4)
	{
		return Line{ new RRR[1]{ { ADD, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

Line addi(size_t argc, const char** argv)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		/***** improve immed check *****/
		if (immed & IMM7_MASK == immed || immed & IMM7_NEG_MASK == IMM7_NEG_MASK)
			return Line{ new RRI[1]{ RRI{ ADDI, argv[1], argv[2], immed } }, 1 };
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
		return Line{ new RRR[1]{ { NAND, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

Line lui(size_t argc, const char** argv)
{
	if (argc == 3)
	{
		uint16_t immed{ imm(argv[2]) };

		if (immed & IMM10_MASK == immed)
			return Line{ new RI[1]{ { LUI, argv[1], immed } }, 1 };
		else
			; // error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line sw(size_t argc, const char** argv)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		/***** improve immed check *****/
		if (immed & IMM7_MASK == immed || immed & IMM7_NEG_MASK == IMM7_NEG_MASK)
			return Line{ new RRI[1]{ RRI{ SW, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
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