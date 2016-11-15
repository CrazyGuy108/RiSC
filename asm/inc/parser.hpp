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

#endif // PARSER_HPP
