#include "instruction.h"

Instruction::Instruction(uint16_t value)
	: value{ value } {}

RRR::RRR(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t regC)
	: Instruction{ opcode | (regA << A_SHIFT) | (regB << B_SHIFT) | regC } {}

RRR::RRR(uint16_t opcode, const char* regA, const char* regB, const char* regC)
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

	*this = RRR{ opcode, regs[operands[0]], regs[operands[1]], regs[operands[2]] };
}

RRI::RRI(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t immC)
	: Instruction{opcode | (regA << A_SHIFT) | (regB << B_SHIFT) | (immC & IMM7_MASK) } {}

RI::RI(uint16_t opcode, uint16_t regA, uint16_t immB)
	: Instruction{ opcode | (regA << A_SHIFT) + (immB & IMM10_MASK) } {}

Line::Line(Instruction* instructions, size_t length)
	: instructions{ instructions }, length{ length } {}

Line::~Line()
{
	if (instructions != nullptr)
		delete[] instructions;
}

/***** move to utilities and rename instruction to line? *****/
Line compile(size_t argc, const char** argv)
{
	if (argc > 0)
	{
		int index{ ops.search(argv[0]) };
		if (index != -1)
		{
			return ops[index](argc, argv);
		}
		else
			; // error: undefined opcode
	}
	else
		return Line{ nullptr, 0 }; // disregard as a blank line
}