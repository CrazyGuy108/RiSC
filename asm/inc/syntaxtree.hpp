#ifndef SYNTAXTREE_HPP
#define SYNTAXTREE_HPP

#include "lexer.hpp"      // for Lexer
#include "syntaxnode.hpp" // for SyntaxNode

class SyntaxTree
{
public:
	SyntaxTree() = default;
	SyntaxTree(const char* program); // lex and parse the given program
	SyntaxTree(Lexer& lexer);        // parse the program using the given lexer

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse the program using the given lexer

private:
	SyntaxNode root; // root of the syntax tree
};

#endif // SYNTAXTREE_HPP
