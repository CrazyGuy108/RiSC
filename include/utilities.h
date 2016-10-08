#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>

typedef uint16_t inst_t; // instruction word
typedef uint16_t data_t; // data word

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
constexpr size_t mem_length = 65536;
constexpr size_t regs_count = 8;

#endif // UTILITIES_H
