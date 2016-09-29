#include "instruction.h"

inst_t rrr(inst_t opcode, inst_t regA, inst_t regB, inst_t regC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | regC;
}

inst_t rrr(inst_t opcode, const char* regA, const char* regB, const char* regC)
{
	int operands[3]
	{
		regs.search(regA),
		regs.search(regB),
		regs.search(regC)
	};

	for (uint8_t i{ 0 }; i < 3; ++i)
	{
		if (operands[i] < 0)
			; // error: undefined operand
	}

	return rrr(opcode, regs[operands[0]], regs[operands[1]], regs[operands[2]]);
}

inst_t rri(inst_t opcode, inst_t regA, inst_t regB, inst_t immC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | (immC & imm7_mask);
}

inst_t rri(inst_t opcode, const char* regA, const char* regB, inst_t immC)
{
	int operands[2]
	{
		regs.search(regA),
		regs.search(regB)
	};

	for (uint8_t i{ 0 }; i < 2; ++i)
	{
		if (operands[i] < 0)
			; // error: undefined operand
	}

	return rri(opcode, regs[operands[0]], regs[operands[1]], immC);
}

inst_t ri(inst_t opcode, inst_t regA, inst_t immB)
{
	return opcode | (regA << a_shift) + (immB & imm10_mask);
}

inst_t ri(inst_t opcode, const char* regA, inst_t immB)
{
	int operand{ regs.search(regA) };

	if (operand >= 0)
		return ri(opcode, regs[operand], immB);
	else
		; // error: undefined operand
}

line_t compile(size_t argc, const char** argv, uint16_t line)
{
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