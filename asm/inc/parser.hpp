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

protected:
	Keyword opcode;
	// operands
};

// similar to a Line but with a label
class LineWithLabel final
	: public Line
{
public:
	LineWithLabel(Lexeme label, Keyword opcode);
	virtual ~LineWithLabel() override final;

private:
	Lexeme label;
};

// base abstract class for operands
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
	virtual ~Register() override final;

private:
	// register
};

// immediate operand
class Immediate final
	: public Operand
{
public:
	virtual ~Immediate() override final;

private:
	// immediate
};

// identifier operand
class Identifier final
	: public Operand
{
public:
	Identifier(Lexeme& id);
	virtual ~Identifier() override final;

private:
	Lexeme id;
};

#endif // PARSER_HPP
