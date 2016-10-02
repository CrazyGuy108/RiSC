#include "../include/operations.h"

OP(add)
{
	if (argc == 4)
		return line_t{ rrr(ADD, reg(argv[1]), reg(argv[2]), reg(argv[3])) };
	else
		throw OperandException{ "add", 3, argc - 1 };
}
/***** add try/catch error handling once implemented *****/
OP(addi)
{
	if (argc == 4)
		return line_t{ rri(ADDI, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "addi", 3, argc - 1 };
}

OP(nand)
{
	if (argc == 4)
		return line_t{ rrr(NAND, reg(argv[1]), reg(argv[2]), reg(argv[3])) };
	else
		throw OperandException{ "nand", 3, argc - 1 };
}

OP(lui)
{
	if (argc == 3)
		return line_t{ ri(LUI, reg(argv[1]), imm(argv[2]) >> lui_shift) };
	else
		throw OperandException{ "lui", 2, argc - 1 };
}

OP(sw)
{
	if (argc == 4)
		return line_t{ rri(SW, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "sw", 3, argc - 1 };
}

OP(lw)
{
	if (argc == 4)
		return line_t{ rri(LW, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "lw", 3, argc - 1 };
}

OP(beq)
{
	if (argc == 4)
		return line_t{ rri(BEQ, reg(argv[1]), reg(argv[2]), imm(argv[3]) - 1 - line) };
	else
		throw OperandException{ "beq", 3, argc - 1 };
}

OP(jalr)
{
	if (argc == 4)
		return line_t{ rri(JALR, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "jalr", 3, argc - 1 };
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