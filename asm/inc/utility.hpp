#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>    // for uint16_t
#include <map>        // for map
#include "lexeme.hpp" // for Lexeme

enum class Keyword
{
	ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR // opcode
};

typedef std::map<Lexeme, Keyword> keyword_map;
typedef uint16_t inst_t;

// keywords mapped to the Keyword enum class
extern const keyword_map keywords;

#endif // UTILITY_HPP
