#include "../inc/token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	return os << t.lexeme << ": " << t.getTypeName();
}

Token::Token(Type type)
	: lexeme{ "null" }, type{ type } {}

Token::Token(const Lexeme& lexeme, Type type)
	: lexeme{ lexeme }, type{ type } {}

const Lexeme& Token::getLexeme() const
{
	return lexeme;
}

Token::Type Token::getType() const
{
	return type;
}

const char* Token::getTypeName() const
{
	switch (type)
	{
	case BEGIN:
		return "begin";
	case END:
		return "end";
	case NEWLINE:
		return "newline";
	case LABEL:
		return "label";
	case REGISTER:
		return "register";
	case IMMEDIATE:
		return "immediate";
	case IDENTIFIER:
		return "identifier";
	case ADD:
		return "opcode_add";
	case ADDI:
		return "opcode_addi";
	case NAND:
		return "opcode_nand";
	case LUI:
		return "opcode_lui";
	case SW:
		return "opcode_sw";
	case LW:
		return "opcode_lw";
	case BEQ:
		return "opcode_beq";
	case JALR:
		return "opcode_jalr";
	case ERROR:
		return "error";
	default:
		return "NULL";
	}
}
