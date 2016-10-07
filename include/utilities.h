#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>

typedef uint16_t inst_t;

// opcodes
constexpr inst_t ADD  = 0x0000;
constexpr inst_t ADDI = 0x2000;
constexpr inst_t NAND = 0x4000;
constexpr inst_t LUI  = 0x6000;
constexpr inst_t SW   = 0x8000;
constexpr inst_t LW   = 0xA000;
constexpr inst_t BEQ  = 0xC000;
constexpr inst_t JALR = 0xE000;

#endif // UTILITIES_H