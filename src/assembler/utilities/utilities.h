#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <vector>

#define OP(name) line_t name##(size_t argc, const char** argv, uint16_t line)

typedef uint16_t inst_t;
typedef std::vector<inst_t> line_t;
typedef OP((*operation_t));

constexpr inst_t ADD        = 0x0000;
constexpr inst_t ADDI       = 0x2000;
constexpr inst_t NAND       = 0x4000;
constexpr inst_t LUI        = 0x6000;
constexpr inst_t SW         = 0x8000;
constexpr inst_t LW         = 0xA000;
constexpr inst_t BEQ        = 0xC000;
constexpr inst_t JALR       = 0xE000;
constexpr inst_t a_shift    = 13;
constexpr inst_t b_shift    = 10;
constexpr inst_t imm7_mask  = 0x007f;
constexpr inst_t imm10_mask = 0x03ff;
constexpr inst_t imm7_min   = -64;
constexpr inst_t imm7_max   = 63;
constexpr inst_t imm10_min  = 0;
constexpr inst_t imm10_max  = 1023;

template<typename T>
class Table;

extern const Table<operation_t> ops;
extern const Table<inst_t>      regs;
extern       Table<inst_t>      symbols;

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

// parses and converts a word into a register
inst_t reg(char* name);

// parses and converts a word into an immediate
inst_t imm(const char* name, uint16_t line = 0);

#include "../instruction/instruction.h"
#include "../operations/operations.h"
#include "../table/table.h"

#endif // UTILITIES_H