#include "operations.h"

op(add)
{
	if (argc == 4)
	{
		return rrr(ADD, argv[1], argv[2], argv[3]);
	}
	else
		; // error: operand count does not match
}

op(addi)
{
	if (argc == 4)
	{
		uint16_t immed{ imm(argv[3]) };

		if (immed >= imm7_min && immed <= imm7_max)
			return rri(ADDI, argv[1], argv[2], immed);
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
		return rrr(NAND, argv[1], argv[2], argv[3]);
	}
	else
		; // error: operand count does not match
}

op(lui)
{
	if (argc == 3)
	{
		uint16_t immed{ imm(argv[2]) };

		if (immed >= imm10_min && immed <= imm10_max)
			return ri(LUI, argv[1], immed);
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

		if (immed >= imm7_min && immed <= imm7_max)
			return rri(SW, argv[1], argv[2], immed);
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

		if (immed >= imm7_min && immed <= imm7_max)
			return rri(LW, argv[1], argv[2], immed);
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

		if (immed >= imm7_min && immed <= imm7_max)
			return rri(BEQ, argv[1], argv[2], immed);
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

		if (immed >= imm7_min && immed <= imm7_max)
			return rri(JALR, argv[1], argv[2], immed);
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