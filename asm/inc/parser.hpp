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

#endif // PARSER_HPP
