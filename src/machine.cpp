#include "../include/machine.h"

void Machine::execute(inst_t inst)
{
	static OPCODE((Machine::* const ops[8])){ &Machine::add, &Machine::addi, &Machine::nand, &Machine::lui, &Machine::sw, &Machine::lw, &Machine::beq, &Machine::jalr };
}

uword_t Machine::read(Read& r)
{
	return access(r);
}

void Machine::write(Write& w)
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

OPCODE(Machine::add)
{

}

OPCODE(Machine::addi)
{

}

OPCODE(Machine::nand)
{

}

OPCODE(Machine::lui)
{

}

OPCODE(Machine::sw)
{

}

OPCODE(Machine::lw)
{

}

OPCODE(Machine::beq)
{

}

OPCODE(Machine::jalr)
{

}
