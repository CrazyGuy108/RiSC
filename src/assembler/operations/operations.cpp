#include "operations.h"

Line add(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		return Line{ new RRR[1]{ { ADD, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

Line addi(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		if (immed >= IMM7_MIN && immed <= IMM7_MAX)
			return Line{ new RRI[1]{ RRI{ ADDI, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line nand(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		return Line{ new RRR[1]{ { NAND, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

Line lui(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 3)
	{
		uint16_t immed{ imm(argv[2]) };

		if (immed >= IMM10_MIN && immed <= IMM10_MAX)
			return Line{ new RI[1]{ { LUI, argv[1], immed } }, 1 };
		else
			; // error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line sw(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		if (immed >= IMM7_MIN && immed <= IMM7_MAX)
			return Line{ new RRI[1]{ RRI{ SW, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line lw(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		if (immed >= IMM7_MIN && immed <= IMM7_MAX)
			return Line{ new RRI[1]{ RRI{ LW, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line beq(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3], line) };

		if (immed >= IMM7_MIN && immed <= IMM7_MAX)
			return Line{ new RRI[1]{ RRI{ BEQ, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}

Line jalr(size_t argc, const char** argv, uint16_t line)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		if (immed >= IMM7_MIN && immed <= IMM7_MAX)
			return Line{ new RRI[1]{ RRI{ JALR, argv[1], argv[2], immed } }, 1 };
		else
			; // either pseudo op or error: immediate too big
	}
	else
		; // error: operand count does not match
}
/***** implement after everything else works *****/
Line nop(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}

Line halt(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}

Line lli(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}

Line movi(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}

Line fill(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}

Line space(size_t argc, const char** argv, uint16_t line)
{
	return Line(); // placeholder
}