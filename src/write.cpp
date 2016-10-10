#include "../include/write.h"

Write::Write(MemUnit unit, size_t addr, uint16_t value)
	: Memory{ unit, addr }, value{ value } {}
