#include "opcodes.h"

Opcode::Opcode(const char* name)
	: value{ opcodes[name].value } {}

Reg::Reg(const char* name)
	: value{ regs[name].value } {}

RRR::RRR(const char* r1, const char* r2, const char* r3)
	: data{ r1, r2, r3 } {}

Add::Add(const char** operands)
	: Opcode{ operands[0] }, RRR{ operands[1], operands[2], operands[3] } {}