#include "../include/machine.h"

uword_t Machine::read(Read& r)
{
	switch (r.unit)
	{
	case Memory::REGISTERS:
		if (r.addr < regs_count)
			return regs[r.addr];
		else
			; // error: reg index out of range
		break;

	case Memory::RAM:
		if (r.addr < ram_length)
			return ram[r.addr];
		else
			; // error: mem index out of range
		break;
	}
}

void Machine::write(Write& w)
{
	switch (w.unit)
	{
	case Memory::REGISTERS:
		if (w.addr < regs_count)
			regs[w.addr] = w.value;
		else
			; // error: reg index out of range
		break;

	case Memory::RAM:
		if (w.addr < ram_length)
			ram[w.addr] = w.value;
		else
			; // error: mem index out of range
		break;
	}
}
