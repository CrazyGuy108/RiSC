#include "../include/result.h"

Result::Result(MemUnit unit, size_t addr, uint16_t value)
	: Memory{ unit, addr }, value{ value } {}