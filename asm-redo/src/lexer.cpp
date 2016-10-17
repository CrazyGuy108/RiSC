#include "../inc/lexer.h"

std::vector<Lexeme> lexer(char* program)
{
	std::vector<Lexeme> lexemes; // keeps track of all the Lexemes the lexer creates
	char* iterator{ program };   // base pointer for tokens

	// iterate through characters
	for (size_t i{ 0 }; program[i] != '\0'; ++i)
	{
		switch (program[i])
		{
		case ' ':
		case '\t':
			iterator[i] = '\0';                     // terminate new substring,
			lexemes.push_back(tokenizer(iterator)); // tokenize it,
			iterator = &iterator[i + 1];            // then reset the base pointer
			break;
		}
	}
}

Lexeme tokenizer(char* name)
{

}
