#ifndef UTILITIES_H
#define UTILITIES_H

#include "../table/table.h"
#include "../instruction/instruction.h"
#include "../pseudo/pseudo.h"

#define ADD 0x0000
#define ADDI 0x2000
#define NAND 0x4000
#define LUI 0x6000
#define SW 0x8000
#define LW 0xA000
#define BEQ 0xC000
#define JALR 0xE000

extern Table<Opcode> opcodes;
extern Table<uint16_t> regs;
extern Table<uint16_t> symbols;
extern Table<Pseudo> pseudos;

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

// parses and converts a number into an immediate
uint16_t imm(const char* name);

#endif // UTILITIES_H