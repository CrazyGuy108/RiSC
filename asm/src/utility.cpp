#include "../inc/utility.hpp"

const opcode_map opcodes
{
	{ "add",  Token::ADD },
	{ "addi", Token::ADDI },
	{ "nand", Token::NAND },
	{ "lui",  Token::LUI },
	{ "sw",   Token::SW },
	{ "lw",   Token::LW },
	{ "beq",  Token::BEQ },
	{ "jalr", Token::JALR }
};
