#include "operations.h"

OP(add)
{
	if (argc == 4)
		return line_t{ rrr(ADD, argv[1], argv[2], argv[3]) };
	else
		; // error: operand count does not match
}
/***** add try/catch error handling once implemented *****/
OP(addi)
{
	if (argc == 4)
		return line_t{ rri(ADDI, argv[1], argv[2], imm(argv[3], 0, imm7_mask)) };
	else
		; // error: operand count does not match
}

OP(nand)
{
	if (argc == 4)
		return line_t{ rrr(NAND, argv[1], argv[2], argv[3]) };
	else
		; // error: operand count does not match
}

OP(lui)
{
	if (argc == 3)
		return line_t{ ri(LUI, argv[1], imm(argv[2], 0, imm10_mask)) };
	else
		; // error: operand count does not match
}

OP(sw)
{
	if (argc == 4)
		return line_t{ rri(SW, argv[1], argv[2], imm(argv[3], 0, imm7_mask)) };
	else
		; // error: operand count does not match
}

OP(lw)
{
	if (argc == 4)
		return line_t{ rri(LW, argv[1], argv[2], imm(argv[3], 0, imm7_mask)) };
	else
		; // error: operand count does not match
}

OP(beq)
{
	if (argc == 4)
		return line_t{ rri(BEQ, argv[1], argv[2], imm(argv[3], line, imm7_mask)) };
	else
		; // error: operand count does not match
}

OP(jalr)
{
	if (argc == 4)
		return line_t{ rri(JALR, argv[1], argv[2], imm(argv[3], 0, imm7_mask)) };
	else
		; // error: operand count does not match
}
/***** implement after everything else works *****/
OP(nop)
{
	return line_t(); // placeholder
}

OP(halt)
{
	return line_t(); // placeholder
}

OP(lli)
{
	return line_t(); // placeholder
}

OP(movi)
{
	return line_t(); // placeholder
}

OP(fill)
{
	return line_t(); // placeholder
}

OP(space)
{
	return line_t(); // placeholder
}