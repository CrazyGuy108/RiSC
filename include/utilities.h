#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>

typedef uint16_t inst_t;

// operand masks
constexpr inst_t OP_MASK  = 0xE000;
constexpr inst_t RA_MASK  = 0x1C00;
constexpr inst_t RB_MASK  = 0x0380;
constexpr inst_t RC_MASK  = 0x0007;
constexpr inst_t I7_MASK  = 0x003F;
constexpr inst_t I10_MASK = 0x03FF;

// operand shifts
constexpr inst_t OP_SHIFT = 13;
constexpr inst_t RA_SHIFT = 10;
constexpr inst_t RB_SHIFT = 7;

// length of various arrays
constexpr size_t MEM_LENGTH = 65536;
constexpr size_t REGS_COUNT = 8;

// corresponding arrays
extern uint16_t mem[MEM_LENGTH];
extern uint16_t regs[REGS_COUNT];

#endif // UTILITIES_H
