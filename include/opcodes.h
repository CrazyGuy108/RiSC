#ifndef OPCODES_H
#define OPCODES_H

#include "result.h"
#include "utilities.h"

#define OPCODE(name) Result name##(inst_t inst, uint16_t* mem)

OPCODE(add);

#endif // OPCODES_H
