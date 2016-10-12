#ifndef RISC_H
#define RISC_H

#include "machine.h"

class RiSC
	: public Machine
{
public:
	virtual void execute(inst_t inst) override final;

private:
	uword_t& mem(uword_t addr);
	uword_t& reg(uword_t addr);

	uword_t ram[ram_length]  = {};
	uword_t regs[regs_count] = {};
};

#endif // RISC_H
