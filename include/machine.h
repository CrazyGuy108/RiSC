#ifndef MACHINE_H
#define MACHINE_H

#include "utilities.h"

class Machine
{
private:
	data_t mem[mem_length]  = {};
	data_t regs[regs_count] = {};
};

#endif // MACHINE_H