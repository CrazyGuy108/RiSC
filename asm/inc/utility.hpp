#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>    // for uint16_t
#include <map>        // for map
#include "lexeme.hpp" // for Lexeme
#include "token.hpp"  // for Token::Type

typedef std::map<Lexeme, Token::Type> opcode_map;
typedef uint16_t inst_t;

extern const opcode_map opcodes;

#endif // UTILITY_HPP
