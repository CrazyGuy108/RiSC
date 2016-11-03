#include "../inc/syntaxtree.hpp"

SyntaxTree::SyntaxTree(const char* program)
{
	parse(program);
}

SyntaxTree::SyntaxTree(Lexer& lexer)
{
	parse(lexer);
}

void SyntaxTree::parse(const char* program)
{
	parse(Lexer{ program });
}
void SyntaxTree::parse(Lexer& lexer)
{
	// parsing time!
}
