#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cstdint>

constexpr uint16_t imm7_min  = -64;
constexpr uint16_t imm7_max  = 63;
constexpr uint16_t imm10_min = 0;
constexpr uint16_t imm10_max = 1023;

#define op(name) line_t name##(size_t argc, const char** argv, uint16_t line)

// opcodes

op(add);
op(addi);
op(nand);
op(lui);
op(sw);
op(lw);
op(beq);
op(jalr);

// pseudo ops

op(nop);
op(halt);
op(lli);
op(movi);
op(fill);
op(space);

#include "../instruction/instruction.h"

#endif // OPERATIONS_H