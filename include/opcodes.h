#ifndef OPCODES_H
#define OPCODES_H

#include "result.h"
#include "utilities.h"

#define OPCODE(name) Result name##(inst_t inst, uint16_t* mem)

OPCODE(add);
OPCODE(addi);
OPCODE(nand);
OPCODE(lui);
OPCODE(sw);
OPCODE(lw);
OPCODE(beq);
OPCODE(jalr);

#endif // OPCODES_H
