#ifndef UTILITIES_H
#define UTILITIES_H

#include "../instruction/instruction.h"
#include "../operations/operations.h"
#include "../table/table.h"

constexpr uint16_t ADD  = 0x0000;
constexpr uint16_t ADDI = 0x2000;
constexpr uint16_t NAND = 0x4000;
constexpr uint16_t LUI  = 0x6000;
constexpr uint16_t SW   = 0x8000;
constexpr uint16_t LW   = 0xA000;
constexpr uint16_t BEQ  = 0xC000;
constexpr uint16_t JALR = 0xE000;

typedef op((*operation_t));

extern Table<operation_t> ops;
extern Table<uint16_t> regs;
extern Table<uint16_t> symbols;

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

// parses and converts a number into an immediate
uint16_t imm(const char* name, uint16_t line = 0);

#endif // UTILITIES_H