#ifndef UTILITIES_H
#define UTILITIES_H

#include "../instruction/instruction.h"
#include "../opcode/opcode.h"
#include "../pseudo/pseudo.h"
#include "../table/table.h"

#define ADD 0x0000
#define ADDI 0x2000
#define NAND 0x4000
#define LUI 0x6000
#define SW 0x8000
#define LW 0xA000
#define BEQ 0xC000
#define JALR 0xE000

typedef Line(*Opcode)(size_t argc, const char** argv);
typedef Line(*Pseudo)(size_t argc, const char** argv);

extern Table<Opcode> opcodes;
extern Table<Pseudo> pseudos;
extern Table<uint16_t> regs;
extern Table<uint16_t> symbols;

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

// parses and converts a number into an immediate
int16_t imm(const char* name);

#endif // UTILITIES_H