#include "../include/machine.h"

void Machine::execute(inst_t inst)
{
	switch (op(inst))
	{
	case add:
		reg(ra(inst)) = reg(rb(inst)) + reg(rc(inst));
		break;

	case addi:
		break;

	case nand:
		reg(ra(inst)) = ~(reg(rb(inst)) & reg(rc(inst)));
		break;

	case lui:
		break;
		
	case sw:
		break;

	case lw:
		break;

	case beq:
		break;

	case jalr:
		break;

	default:
		; // error: undefined opcode (should never happen)
	}
}

uword_t& Machine::mem(uword_t addr)
{
	if (addr < ram_length)
		return ram[addr];
	else
		; // error: mem index out of range
}

uword_t& Machine::reg(uword_t addr)
{
	if (addr < regs_count)
		return regs[addr];
	else
		; // error: reg index out of range
}
