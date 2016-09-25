#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// prototypes
class Line;

#include <cstdint>
#include <vector>
#include "../utilities/utilities.h"

constexpr inst_t a_shift    = 13;
constexpr inst_t b_shift    = 10;
constexpr inst_t imm7_mask  = 0x007f;
constexpr inst_t imm10_mask = 0x03ff;

typedef uint16_t inst_t;
typedef std::vector<inst_t> line_t;

line_t rrr(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t regC);
line_t rrr(uint16_t opcode, const char* regA, const char* regB, const char* regC);

line_t rri(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t immC);
line_t rri(uint16_t opcode, const char* regA, const char* regB, uint16_t immC);

line_t ri(uint16_t opcode, uint16_t regA, uint16_t immB);
line_t ri(uint16_t opcode, const char* regA, uint16_t immB);


// takes in a parsed line of code to produce a series of bytecode instructions
line_t compile(size_t argc, const char** argv, uint16_t line);

#endif // INSTRUCTION_H