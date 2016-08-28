#ifndef UTILITIES_H
#define UTILITIES_H

#include "../symboltable/symboltable.h"

#define ADD 0x0000
#define ADDI 0x2000
#define NAND 0x4000
#define LUI 0x6000
#define SW 0x8000
#define LW 0xA000
#define BEQ 0xC000
#define JALR 0xE000

typedef Table<uint16_t> SymbolTable;

extern Table<uint16_t> opcodes;
extern Table<uint16_t> regs;
extern Table<uint16_t> imms;
extern Table<uint16_t> symbols;

#endif // UTILITIES_H