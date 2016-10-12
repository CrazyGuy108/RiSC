#ifndef RISC_H
#define RISC_H

#include "machine.h"

class RiSC
	: public Machine
{
public:
	virtual void execute(inst_t inst) override final;
};

#endif // RISC_H
