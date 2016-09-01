#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "instruction/instruction.h"
#include "opcode/opcode.h"
#include "pseudo/pseudo.h"
#include "table/table.h"
#include "utilities/utilities.h"

char* assemble(const char* program);

#endif // ASSEMBLER_H