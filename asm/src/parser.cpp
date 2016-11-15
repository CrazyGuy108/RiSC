#include "../inc/parser.hpp"

Parser::Parser(Lexer& lexer)
{
	parse(lexer);
}

void Parser::parse(Lexer& lexer)
{
	Line* line{ nullptr };
	Token token;
	while (!lexer.empty())
	{
		// get next token
		// skip if newline/error
		// get label, deciding if it should be a LineWithLabel or Line
		// get opcode
		// get operands
		// add newly constructed line to the Line stream and reset
	}

	if(line != nullptr)
		; // error: end of file but incomplete line
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

void Line::setOpcode(Keyword opcode)
{
	this->opcode = opcode;
}

void Line::addOperand(Operand* operand)
{
	operands.push_back(operand);
}

LineWithLabel::LineWithLabel(const Lexeme& label)
	: label{ label } {}

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
