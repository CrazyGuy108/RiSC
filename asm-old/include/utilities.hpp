#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstdint>   // for uint16_T
#include <vector>    // for vector
#include "table.hpp" // for Table

#define OP(name) line_t name##(size_t argc, const char** argv, uint16_t line)

typedef uint16_t inst_t;
typedef std::vector<inst_t> line_t;

constexpr inst_t ADD        = 0x0000;
constexpr inst_t ADDI       = 0x2000;
constexpr inst_t NAND       = 0x4000;
constexpr inst_t LUI        = 0x6000;
constexpr inst_t SW         = 0x8000;
constexpr inst_t LW         = 0xA000;
constexpr inst_t BEQ        = 0xC000;
constexpr inst_t JALR       = 0xE000;
constexpr inst_t imm7_mask  = 0x007F;
constexpr inst_t imm10_mask = 0x03FF;
constexpr inst_t movi_mask  = 0xFFBF;
constexpr inst_t a_shift    = 10;
constexpr inst_t b_shift    = 7;
constexpr inst_t lui_shift  = 6;

extern Table<inst_t> symbols;

#endif // UTILITIES_HPP
