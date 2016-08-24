#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "symboltable/symboltable.h"
#include "opcodes/opcodes.h"

char* assemble(const char* program);

#endif // ASSEMBLER_H