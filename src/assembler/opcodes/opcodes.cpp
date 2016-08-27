#include "opcodes.h"

Opcode::Opcode(uint16_t value)
	: value{ value } {}

Reg::Reg(const char* name)
	: value{ regs[name].value } {}

RRR::RRR(const char* r1, const char* r2, const char* r3)
	: data{ r1, r2, r3 } {}

Add::Add(uint16_t opcode, const char* r1, const char* r2, const char* r3)
	: Opcode{ opcode }, RRR{ r1, r2, r3 } {}