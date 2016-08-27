#include "opcodes.h"

Opcode::Opcode(uint16_t opcode)
	: opcode{ opcode } {}

Reg::Reg(const char* name)
	: value{ regs[name].value } {}

RRR::RRR(const char* r1, const char* r2, const char* r3)
	: data{ r1, r2, r3 } {}