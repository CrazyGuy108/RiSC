#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>

typedef uint16_t inst_t;

// opcodes
constexpr inst_t add  = 0x0000;
constexpr inst_t addi = 0x2000;
constexpr inst_t nand = 0x4000;
constexpr inst_t lui  = 0x6000;
constexpr inst_t sw   = 0x8000;
constexpr inst_t lw   = 0xA000;
constexpr inst_t beq  = 0xC000;
constexpr inst_t jalr = 0xE000;

#endif // UTILITIES_H