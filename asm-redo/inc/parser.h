#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"      // for Lexer
#include "syntaxtree.h" // for SyntaxTree

class Parser
{
public:
	Parser() = default;
	Parser(const char* program); // lex and parse the given program
	Parser(Lexer& lexer);        // parse program using the given lexer

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse program using the given lexer

private:
	SyntaxTree ast; // syntax tree to be generated
};

#endif // PARSER_H
