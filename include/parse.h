#ifndef PARSE_H
#define PARSE_H

#include <cstdint>      // for uint16_t
#include <iostream>     // for std::cout
#include "operations.h" // for opcode functions
#include "table.h"      // for Table
#include "utilities.h"  // for typedefs

// converts a word into a register
inst_t reg(const char* name);

// converts a word into an immediate
inst_t imm(const char* name);

void compile(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes);

#endif // PARSE_H