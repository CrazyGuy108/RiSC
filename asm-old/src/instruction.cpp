#include "../include/instruction.hpp"

inst_t rrr(inst_t opcode, inst_t regA, inst_t regB, inst_t regC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | regC;
}

inst_t rri(inst_t opcode, inst_t regA, inst_t regB, inst_t immC)
{
	return opcode | (regA << a_shift) | (regB << b_shift) | (immC & imm7_mask);
}

inst_t ri(inst_t opcode, inst_t regA, inst_t immB)
{
	return opcode | (regA << a_shift) + (immB & imm10_mask);
}
