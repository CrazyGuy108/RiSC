#include "../inc/lexer.h"

std::vector<Lexeme> lexer(char* program)
{
	std::vector<Lexeme> lexemes;

	// iterate through characters
	for (size_t i{ 0 }; program[i] != '\0'; ++i)
	{
		if (program[i] == ' ')
			; // tokenize
	}
}

Lexeme tokenize(char* name)
{

}
