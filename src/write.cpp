#include "../include/write.h"

Write::Write(MemUnit unit, size_t addr, uword_t value)
	: Memory{ unit, addr }, value{ value } {}
