#include "../inc/parsetree.hpp"

ParseTree::ParseTree(const char* program)
{
	parse(program);
}

ParseTree::ParseTree(Lexer& lexer)
{
	parse(lexer);
}

void ParseTree::parse(const char* program)
{
	parse(Lexer{ program });
}
void ParseTree::parse(Lexer& lexer)
{
	// parsing time!
}
