#ifndef SYNTAXTREE_HPP
#define SYNTAXTREE_HPP

#include "token.hpp" // for Token

class SyntaxTree
{
public:
	SyntaxTree() = default;

	void add(Token t); // adds a Token to the syntax tree

private:
	// syntax tree stuff
};

#endif // SYNTAXTREE_HPP
