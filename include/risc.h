#ifndef RISC_H
#define RISC_H

#include "utilities.h" // for typedefs

class RiSC
{
public:
	RiSC();

	void load(uword_t* program, uword_t length); // load a program into memory
	void execute(); // execute the program where the PC left off

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
