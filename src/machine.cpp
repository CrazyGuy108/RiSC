#include "../include/machine.h"

void Machine::execute(inst_t inst)
{
	switch (inst & op_mask)
	{
	case add:
		write(Write{ Memory::REGISTERS, (size_t)((inst & ra_mask) >> ra_shift), (uword_t)(read(Read{ Memory::REGISTERS, (size_t)((inst & rb_mask) >> rb_shift) }) + read(Read{ Memory::REGISTERS, (size_t)(inst & rc_mask) })) });
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

uword_t Machine::read(Read r)
{
	return access(r);
}

void Machine::write(Write w)
{
	access(w) = w.value;
}

uword_t& Machine::access(Memory& m)
{
	switch (m.unit)
	{
	case Memory::REGISTERS:
		if (m.addr < regs_count)
			return regs[m.addr];
		else
			; // error: reg index out of range
		break;

	case Memory::RAM:
		if (m.addr < ram_length)
			return ram[m.addr];
		else
			; // error: mem index out of range
		break;
	}
}
