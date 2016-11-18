#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>    // for uint16_t
#include <map>        // for map
#include "lexeme.hpp" // for Lexeme
#include "token.hpp"  // for Token::Type

typedef uint16_t                      inst_t;
typedef std::map<Lexeme, Token::Type> opcode_map;

extern const opcode_map opcodes;

// converts a Token::Type to string
const char* getTypeName(Token::Type type);

#endif // UTILITY_HPP
