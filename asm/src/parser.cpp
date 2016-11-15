#include "../inc/parser.hpp"

Parser::Parser(Lexer& lexer)
{
	parse(lexer);
}

void Parser::parse(Lexer& lexer)
{
	// parsing stuff
}

Line::Line(Keyword opcode)
	: opcode{ opcode } {}

Line::~Line()
{
	for(auto i : operands)
		if(i != nullptr)
			delete i;
}

Keyword Line::getOpcode() const
{
	return opcode;
}

Operand* Line::getOperand(size_t index)
{
	return operands[index];
}

const Operand* Line::getOperand(size_t index) const
{
	return operands[index];
}

void Line::addOperand(Operand* operand)
{
	operands.push_back(operand);
}

LineWithLabel::LineWithLabel(Keyword opcode, const Lexeme& label)
	: Line{ opcode }, label{ label } {}

const Lexeme& LineWithLabel::getLabel() const
{
	return label;
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
