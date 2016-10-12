#ifndef RISC_H
#define RISC_H

#include "utilities.h" // for typedefs

class RiSC
{
public:
	RiSC();

	void execute(inst_t inst);

private:
	uword_t& mem(uword_t addr);
	uword_t& reg(uword_t addr);

	uword_t ram[ram_length];
	uword_t regs[regs_count];
};

#endif // RISC_H
