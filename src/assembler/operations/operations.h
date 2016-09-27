#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cstdint>
#include "../instruction/instruction.h"

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