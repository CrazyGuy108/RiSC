#include "../include/machine.h"

void Machine::commit(Result& r)
{
	switch (r.unit)
	{
	case Memory::REGISTERS:
		if (r.addr < regs_count)
			regs[r.addr] = r.value;
		else
			; // error: reg index out of range
		break;

	case Memory::RAM:
		if (r.addr < ram_length)
			ram[r.addr] = r.value;
		else
			; // error: mem index out of range
		break;
	}
}
