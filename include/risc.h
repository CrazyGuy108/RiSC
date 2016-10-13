#ifndef RISC_H
#define RISC_H

#include "utilities.h" // for typedefs

class RiSC
{
public:
	RiSC();

	uword_t execute(inst_t inst);

	uword_t getRam(uword_t addr);
	uword_t getReg(uword_t addr);

private:
	uword_t& mem(uword_t addr);
	uword_t& reg(uword_t addr);

	uword_t ram[ram_length];
	uword_t regs[regs_count];

	uword_t pc;
};

#endif // RISC_H
