#include "../inc/parser.hpp"

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "opcode: " << getTypeName(line.opcode);

	// add the label if present
	const LineWithLabel* linewithlabel{ dynamic_cast<const LineWithLabel*>(&line) };
	if(linewithlabel != nullptr)
		os << "\n label: " << linewithlabel->getLabel();

	// print operands
	if (!line.operands.empty())
		for (const Operand* i : line.operands)
			os << "\n " << *i;

	return os;
}

std::ostream& operator<<(std::ostream& os, const Operand& operand)
{
	if (dynamic_cast<const Register*>(&operand) != nullptr)
		return os << "register: " << dynamic_cast<const Register*>(&operand)->getReg();
	else if (dynamic_cast<const Immediate*>(&operand) != nullptr)
		return os << "immediate: " << dynamic_cast<const Immediate*>(&operand)->getImm();
	else if (dynamic_cast<const Identifier*>(&operand) != nullptr)
		return os << "identifier: " << dynamic_cast<const Identifier*>(&operand)->getID();
	else
		return os << "error";
}

Parser::Parser(Lexer& lexer)
	: errors{ 0 }
{
	parse(lexer);
}

Parser::~Parser()
{
	for(auto i : lines)
		if(i != nullptr)
			delete i;
}

void Parser::parse(Lexer& lexer)
{
	Line* line{ nullptr };
	Token token;
	size_t currentLine{ 0 };
	while (!lexer.empty())
	{
		token = lexer.next();

		if (token.getType() == Token::NEWLINE)
		{
			++currentLine;
			continue;
		}

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
		{
			std::cout << "parser error(" << currentLine << "): expected opcode but was given " << getTypeName(token.getType()) << " instead\n";
			++errors;
			delete line;
			line = nullptr;
			continue;
		}

		token = lexer.next();

		// get operands
		while (token.getType() != Token::NEWLINE)
		{
			try
			{
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
					std::cout << "parser error(" << currentLine << "): expected operand but was given " << getTypeName(token.getType()) << " instead\n";
					++errors;
				}
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << "parser error(" << currentLine << "): invalid " << e.what() << " \"" << token.getLexeme() << "\"\n";
				++errors;
			}

			token = lexer.next();
		}

		// add newly constructed line to the Line stream and reset
		lines.push_back(line);
		line = nullptr;
		++currentLine;
	}

	it = lines.cbegin();
}

Line* Parser::next()
{
	if(!empty())
		return *it++;
	else
		return nullptr;
}

size_t Parser::getErrors() const
{
	return errors;
}

bool Parser::empty() const
{
	return it == lines.cend();
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
	if (lexeme.length() == 2 &&
	    lexeme[0] == 'r' &&
	    lexeme[1] >= '0' &&
	    lexeme[1] <= '7')
		reg = lexeme[1] - '0';
	else
		throw std::invalid_argument{ "register" };
}

inst_t Register::getReg() const
{
	return reg;
}

Immediate::Immediate(inst_t imm)
	: imm{ imm } {}

Immediate::Immediate(const Lexeme& lexeme)
{
	size_t sz{ 0 };
	int value;
	std::string str{ lexeme.getBeg(), lexeme.length() };
	try
	{
		value = std::stoi(str, &sz, 0);
	}
	catch (std::logic_error& e)
	{
		throw std::invalid_argument{ "immediate" };
	}

	if (sz != 0) // conversion succeeded
		imm = value;
	else
		throw std::invalid_argument{ "immediate" };
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
