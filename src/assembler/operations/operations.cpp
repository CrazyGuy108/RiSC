#include "operations.h"

op(add)
{
	if (argc == 4)
	{
		return Line{ new RRR[1]{ { ADD, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

op(addi)
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

op(nand)
{
	if (argc == 4)
	{
		return Line{ new RRR[1]{ { NAND, argv[1], argv[2], argv[3] } }, 1 };
	}
	else
		; // error: operand count does not match
}

op(lui)
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

op(sw)
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

op(lw)
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

op(beq)
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

op(jalr)
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
/***** implement after everything else works *****
op(nop)
{
	return Line(); // placeholder
}

op(halt)
{
	return Line(); // placeholder
}

op(lli)
{
	return Line(); // placeholder
}

op(movi)
{
	return Line(); // placeholder
}

op(fill)
{
	return Line(); // placeholder
}

op(space)
{
	return Line(); // placeholder
}*/