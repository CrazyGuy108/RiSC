#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../utilities/utilities.h"

line_t rrr(inst_t opcode, inst_t regA, inst_t regB, inst_t regC);
line_t rrr(inst_t opcode, const char* regA, const char* regB, const char* regC);

line_t rri(inst_t opcode, inst_t regA, inst_t regB, inst_t immC);
line_t rri(inst_t opcode, const char* regA, const char* regB, inst_t immC);

line_t ri(inst_t opcode, inst_t regA, inst_t immB);
line_t ri(inst_t opcode, const char* regA, inst_t immB);

// takes in a parsed line of code to produce a series of bytecode instructions
line_t compile(size_t argc, char** argv, uint16_t line);

#endif // INSTRUCTION_H