#ifndef SYNTAXTREE_HPP
#define SYNTAXTREE_HPP

#include "lexer.cpp" // for Lexer

class SyntaxTree
{
public:
	SyntaxTree() = default;
	SyntaxTree(const char* program); // lex and parse the given program
	SyntaxTree(Lexer& lexer);        // parse the program using the given lexer

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse the program using the given lexer

private:
	// syntax tree stuff
};

#endif // SYNTAXTREE_HPP
