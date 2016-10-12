#ifndef MACHINE_H
#define MACHINE_H

#include "utilities.h" // for typedefs

class Machine
{
public:
	virtual void execute(inst_t inst) = 0;
};

#endif // MACHINE_H
