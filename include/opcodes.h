#ifndef OPCODES_H
#define OPCODES_H

#include "write.h"     // for Write
#include "utilities.h" // for typedefs

#define OPCODE(name) Write name##(inst_t inst)

OPCODE(add);
OPCODE(addi);
OPCODE(nand);
OPCODE(lui);
OPCODE(sw);
OPCODE(lw);
OPCODE(beq);
OPCODE(jalr);

#endif // OPCODES_H
