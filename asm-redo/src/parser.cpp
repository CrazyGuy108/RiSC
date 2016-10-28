#include "../inc/parser.h"

Parser::Parser(char* program)
{
	parse(program);
}

Parser::Parser(Lexer& lexer)
{
	parse(lexer);
}

void Parser::parse(char* program)
{
	Lexer lexer{ program };
	parse(lexer);
}

void Parser::parse(Lexer& lexer)
{

}
