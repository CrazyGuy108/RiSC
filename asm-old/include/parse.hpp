#ifndef PARSE_HPP
#define PARSE_HPP

#include <cstdint>        // for uint16_t
#include "operations.hpp" // for opcode functions
#include "table.hpp"      // for Table
#include "utilities.hpp"  // for typedefs

// converts a word into a register
inst_t reg(const char* name);

// converts a word into an immediate
inst_t imm(const char* name);

#endif // PARSE_HPP
