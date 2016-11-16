#include "../inc/parser.hpp"

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "opcode: " << getTypeName(line.opcode);
	if(!line.operands.empty())
		os << '\n';

	// print operands
	for (const Operand* i : line.operands)
		os << *i;

	return os;
}

std::ostream& operator<<(std::ostream& os, const Operand& operand)
{
	return os; // placeholder
}

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
		token = lexer.next();

		if(token.getType() == Token::NEWLINE || token.getType() == Token::ERROR)
			continue;

		// get label, deciding if it should be a LineWithLabel or Line
		if (token.getType() == Token::LABEL)
		{
			line = new LineWithLabel{ token.getLexeme() };
			token = lexer.next();
		}
		else
			line = new Line{};

		// get opcode
		if (token.getType() >= Token::ADD && token.getType() <= Token::JALR)
			line->setOpcode(token.getType());
		else
			; // error: invalid opcode

		// get operands
		while (token.getType() != Token::NEWLINE)
		{
			token = lexer.next();
			switch (token.getType())
			{
			case Token::REGISTER:
				line->addOperand(new Register{ token.getLexeme() });
				break;

			case Token::IMMEDIATE:
				line->addOperand(new Immediate{ token.getLexeme() });
				break;

			case Token::IDENTIFIER:
				line->addOperand(new Identifier{ token.getLexeme() });
				break;

			default:
				; // error: invalid operand
			}
		}

		// add newly constructed line to the Line stream and reset
		lines.push(line);
		line = nullptr;
	}

	if(line != nullptr)
		; // error: end of file but incomplete line
}

Line::Line(Token::Type opcode)
	: opcode{ opcode } {}

Line::~Line()
{
	for(auto i : operands)
		if(i != nullptr)
			delete i;
}

Token::Type Line::getOpcode() const
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

void Line::setOpcode(Token::Type opcode)
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

Register::Register(const Lexeme& lexeme)
{

}

inst_t Register::getReg() const
{
	return reg;
}

Immediate::Immediate(inst_t imm)
	: imm{ imm } {}

Immediate::Immediate(const Lexeme& lexeme)
{

}

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
