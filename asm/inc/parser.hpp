#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexeme.hpp"  // for Lexeme
#include "lexer.hpp"   // for Lexer
#include "utility.hpp" // for Keyword

// verifies and organizes a stream of tokens from the Lexer
class Parser
{
public:
	Parser() = default;
	Parser(Lexer& lexer);

	void parse(Lexer& lexer); // parse using the given lexer

private:
	// stream of lines
};

// represents a parsed and tokenized line of code
class Line
{
public:
	Line(Keyword opcode);
	virtual ~Line();

	Keyword getOpcode() const;

protected:
	Keyword opcode;
	// operands
};

// similar to a Line but with a label
class LineWithLabel final
	: public Line
{
public:
	LineWithLabel(Keyword opcode, const Lexeme& label);
	virtual ~LineWithLabel() override final = default;

	const Lexeme& getLabel() const;

private:
	Lexeme label;
};

// abstract base class for operands
class Operand
{
public:
	Operand() = default;
	virtual ~Operand() = 0;
};

// register operand
class Register final
	: public Operand
{
public:
	Register(inst_t reg);
	virtual ~Register() override final = default;

	inst_t getReg() const;

private:
	inst_t reg;
};

// immediate operand
class Immediate final
	: public Operand
{
public:
	Immediate(inst_t imm);
	virtual ~Immediate() override final = default;

	inst_t getImm() const;

private:
	inst_t imm;
};

// identifier operand
class Identifier final
	: public Operand
{
public:
	Identifier(const Lexeme& id);
	virtual ~Identifier() override final = default;

	const Lexeme& getID() const;

private:
	Lexeme id;
};

#endif // PARSER_HPP
