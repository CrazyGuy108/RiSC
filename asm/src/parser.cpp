#include "../inc/parser.hpp"

Parser::Parser(Lexer& lexer)
{
	parse(lexer);
}

void Parser::parse(Lexer& lexer)
{
	// parsing stuff
}

Operand::~Operand()
{}

Register::Register(inst_t reg)
	: reg{ reg } {}

inst_t Register::getReg() const
{
	return reg;
}

Immediate::Immediate(inst_t imm)
	: imm{ imm } {}

inst_t Immediate::getImm() const
{
	return imm;
}

Identifier::Identifier(const Lexeme& id)
	: id{ id } {}

const Lexeme& Identifier::getID() const
{
	return id;
}
