#include "../include/machine.h"

void Machine::execute(inst_t inst)
{
	switch (inst & op_mask >> op_shift)
	{

	}
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
