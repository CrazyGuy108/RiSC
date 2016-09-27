#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cstdint>
#include "../instruction/instruction.h"

constexpr uint16_t imm7_min  = -64;
constexpr uint16_t imm7_max  = 63;
constexpr uint16_t imm10_min = 0;
constexpr uint16_t imm10_max = 1023;

#define OP(name) line_t name##(size_t argc, const char** argv, uint16_t line)

// opcodes

OP(add);
OP(addi);
OP(nand);
OP(lui);
OP(sw);
OP(lw);
OP(beq);
OP(jalr);

// pseudo ops

OP(nop);
OP(halt);
OP(lli);
OP(movi);
OP(fill);
OP(space);

#endif // OPERATIONS_H