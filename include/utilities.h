#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint> // for int16_t and uint16_t

typedef uint16_t inst_t;  // instruction word
typedef uint16_t uword_t; // unsigned data word
typedef int16_t  sword_t; // signed data word

// opcodes
constexpr inst_t add  = 0x0000;
constexpr inst_t addi = 0x2000;
constexpr inst_t nand = 0x4000;
constexpr inst_t lui  = 0x6000;
constexpr inst_t sw   = 0x8000;
constexpr inst_t lw   = 0xC000;
constexpr inst_t jalr = 0xE000;

// operand masks
constexpr inst_t op_mask  = 0xE000;
constexpr inst_t ra_mask  = 0x1C00;
constexpr inst_t rb_mask  = 0x0380;
constexpr inst_t rc_mask  = 0x0007;
constexpr inst_t i7_mask  = 0x003F;
constexpr inst_t i10_mask = 0x03FF;

// operand shifts
constexpr inst_t op_shift = 13;
constexpr inst_t ra_shift = 10;
constexpr inst_t rb_shift = 7;

// length of various arrays
constexpr size_t ram_length = 65536;
constexpr size_t regs_count = 8;

#endif // UTILITIES_H
