#ifndef PARSE_H
#define PARSE_H

#include "../utilities/utilities.h"

// converts a word into a register
inst_t reg(const char* name);

// converts a word into an immediate
inst_t imm(const char* name, uint16_t line = 0, inst_t mask = 0xffff);

// takes in a parsed line of code to produce a series of bytecode instructions
line_t compile(size_t argc, const char** argv, uint16_t line);

#endif // PARSE_H