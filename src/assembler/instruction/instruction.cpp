#include "instruction.h"

line_t rrr(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t regC)
{
	return line_t{ opcode | (regA << A_SHIFT) | (regB << B_SHIFT) | regC };
}

line_t rrr(uint16_t opcode, const char* regA, const char* regB, const char* regC)
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

line_t rri(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t immC)
{
	return line_t{ opcode | (regA << A_SHIFT) | (regB << B_SHIFT) | (immC & IMM7_MASK) };
}

line_t rri(uint16_t opcode, const char* regA, const char* regB, uint16_t immC)
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

line_t ri(uint16_t opcode, uint16_t regA, uint16_t immB)
{
	return line_t{ opcode | (regA << A_SHIFT) + (immB & IMM10_MASK) };
}

line_t ri(uint16_t opcode, const char* regA, uint16_t immB)
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