#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "lexer.hpp"     // for Lexer
#include "parsenode.hpp" // for ParseNode

class ParseTree
{
public:
	ParseTree() = default;
	ParseTree(const char* program); // lex and parse the given program
	ParseTree(Lexer& lexer);        // parse the program using the given lexer

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse the program using the given lexer

private:
	ParseNode root; // root of the parse tree
};

#endif // PARSETREE_HPP
