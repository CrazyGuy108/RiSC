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

const char* getTypeName(Token::Type type)
{
	switch (type)
	{
	case Token::BEGIN:
		return "begin";
	case Token::END:
		return "end";
	case Token::NEWLINE:
		return "newline";
	case Token::LABEL:
		return "label";
	case Token::REGISTER:
		return "register";
	case Token::IMMEDIATE:
		return "immediate";
	case Token::IDENTIFIER:
		return "identifier";
	case Token::ADD:
		return "opcode_add";
	case Token::ADDI:
		return "opcode_addi";
	case Token::NAND:
		return "opcode_nand";
	case Token::LUI:
		return "opcode_lui";
	case Token::SW:
		return "opcode_sw";
	case Token::LW:
		return "opcode_lw";
	case Token::BEQ:
		return "opcode_beq";
	case Token::JALR:
		return "opcode_jalr";
	case Token::ERROR:
		return "error";
	default:
		return "NULL";
	}
}
