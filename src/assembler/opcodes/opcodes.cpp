#include "opcodes.h"

Reg::Reg(const char* name)
	: value{ regs.at(name).value } {}