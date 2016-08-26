#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "table/table.h"
#include "symboltable/symboltable.h"
#include "operands/operands.h"
#include "opcodes/opcodes.h"

char* assemble(const char* program);

#endif // ASSEMBLER_H