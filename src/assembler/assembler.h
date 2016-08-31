#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "table/table.h"
#include "utilities/utilities.h"
#include "instruction/instruction.h"
#include "pseudo/pseudo.h"
#include "table/table.h"

char* assemble(const char* program);

#endif // ASSEMBLER_H