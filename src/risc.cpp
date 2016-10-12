#include "../include/risc.h"

void RiSC::execute(inst_t inst)
{
	switch (op(inst))
	{
	case add:
		reg(ra(inst)) = reg(rb(inst)) + reg(rc(inst));
		break;

	case addi:
		reg(ra(inst)) = reg(rb(inst)) + i7(inst);
		break;

	case nand:
		reg(ra(inst)) = ~(reg(rb(inst)) & reg(rc(inst)));
		break;

	case lui:
		reg(ra(inst)) = i10(inst);
		break;

	case sw:
		mem(reg(rb(inst)) + i7(inst)) = reg(ra(inst));
		break;

	case lw:
		reg(ra(inst)) = mem(reg(rb(inst)) + i7(inst));
		break;

	case beq:
		break;

	case jalr:
		break;

	default:
		; // error: undefined opcode (should never happen)
	}
}
