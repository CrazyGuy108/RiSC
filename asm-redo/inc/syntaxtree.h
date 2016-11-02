#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "token.h" // for Token

class SyntaxTree
{
public:
	SyntaxTree() = default;

	void add(Token t); // adds a Token to the syntax tree

private:
	// syntax tree stuff
};

#endif // SYNTAXTREE_H
