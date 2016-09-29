#include "instruction.h"

inst_t rrr(inst_t opcode, inst_t regA, inst_t regB, inst_t regC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | regC;
}

inst_t rrr(inst_t opcode, const char* regA, const char* regB, const char* regC)
{
	return rrr(opcode, reg(regA), reg(regB), reg(regC));
}

inst_t rri(inst_t opcode, inst_t regA, inst_t regB, inst_t immC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | (immC & imm7_mask);
}

inst_t rri(inst_t opcode, const char* regA, const char* regB, inst_t immC)
{
	return rri(opcode, reg(regA), reg(regB), immC);
}

inst_t ri(inst_t opcode, inst_t regA, inst_t immB)
{
	return opcode | (regA << a_shift) + (immB & imm10_mask);
}

inst_t ri(inst_t opcode, const char* regA, inst_t immB)
{
	return ri(opcode, reg(regA), immB);
}

line_t compile(size_t argc, const char** argv, uint16_t line)
{
	const Table<operation_t> ops
	{
		{ ".fill",  &fill },
		{ ".space", &space },
		{ "add",    &add },
		{ "addi",   &addi },
		{ "beq",    &beq },
		{ "halt",   &halt },
		{ "jalr",   &jalr },
		{ "lli",    &lli },
		{ "lui",    &lui },
		{ "lw",	    &lw },
		{ "movi",   &movi },
		{ "nand",   &nand },
		{ "nop",    &nop },
		{ "sw",	    &sw }
	};

	if (argc > 0)
	{
		int index{ ops.search(argv[0]) };
		if (index != -1)
		{
			return ops[index](argc, argv, line);
		}
		else
			; // error: undefined opcode
	}
	else
		return line_t{}; // disregard as a blank line
}