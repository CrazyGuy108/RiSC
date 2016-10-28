#ifndef PARSER_H
#define PARSER_H

#include "lexer.h" // for Lexer

class Parser
{
public:
	Parser() = default;
	Parser(char* program); // lex and parse the given program
	Parser(Lexer& lexer);  // parse program using the given lexer

	void parse(char* program); // lex and parse the given program
	void parse(Lexer& lexer);  // parse program using the given lexer
};

#endif // PARSER_H
