#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "token.h"

class SyntaxTree
{
public:
	SyntaxTree() = default;

	void add(Token t);

private:
	// syntax tree stuff
};

#endif // SYNTAXTREE_H
