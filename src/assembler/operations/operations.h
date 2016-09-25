#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cstdint>

#define IMM7_MIN -64
#define IMM7_MAX 63
#define IMM10_MIN 0
#define IMM10_MAX 1023

#define op(name) Line name(size_t argc, const char** argv, uint16_t line)

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