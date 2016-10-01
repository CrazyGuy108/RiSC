#ifndef PARSE_H
#define PARSE_H

#include <cstdint>      // for uint16_t
#include "operations.h" // for opcode functions
#include "table.h"      // for Table
#include "utilities.h"  // for typedefs

// converts a word into a register
inst_t reg(const char* name);

// converts a word into an immediate
inst_t imm(const char* name);

// takes in a parsed line of code to produce a series of bytecode instructions
line_t compile(size_t argc, char** argv, uint16_t line);

#endif // PARSE_H