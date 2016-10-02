#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "instruction.h" // for rrr/rri/ri
#include "parse.h"       // for reg()/imm()
#include "utilities.h"   // for macros/constants

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

#endif // OPERATIONS_H