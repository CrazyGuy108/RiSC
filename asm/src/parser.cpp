#include "../inc/parser.hpp"

Parser::Parser(const char* program)
{
	parse(program);
}

Parser::Parser(Lexer& lexer)
{
	parse(lexer);
}

void Parser::parse(const char* program)
{
	parse(Lexer{ program });
}

void Parser::parse(Lexer& lexer)
{

}
