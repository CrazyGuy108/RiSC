#include "../include/machine.h"

void Machine::execute(inst_t inst)
{
	switch (inst & op_mask)
	{
	case add:
		access(REGISTERS, (inst & ra_mask) >> ra_shift) = access(REGISTERS, (inst & rb_mask) >> rb_shift) + access(REGISTERS, inst & rc_mask);
		break;

	case addi:
		break;

	case nand:
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

uword_t& Machine::access(MemUnit unit, uword_t addr)
{
	switch (unit)
	{
	case REGISTERS:
		if (addr < regs_count)
			return regs[addr];
		else
			; // error: reg index out of range
		break;

	case RAM:
		if (addr < ram_length)
			return ram[addr];
		else
			; // error: mem index out of range
		break;
	}
}
