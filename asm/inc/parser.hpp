#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp" // for Lexer

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
	// opcode
	// operands
};

// similar to a Line but with a label
class LineWithLabel
	: public Line
{
public:
	// label
};

#endif // PARSER_HPP
