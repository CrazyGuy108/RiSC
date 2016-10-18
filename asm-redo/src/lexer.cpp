#include "../inc/lexer.h"

std::vector<Lexeme> lexer(char* program)
{
	std::vector<Lexeme> lexemes; // keeps track of all the Lexemes the lexer creates
	char* iterator{ program };   // base pointer for tokens
	bool foundSpace{ true };     // if the lexer has found a space, this will be true

	// iterate through characters
	for (size_t i{ 0 }; program[i] != '\0'; ++i)
	{
		switch (program[i])
		{
		case ' ':
		case '\t':
			if (foundSpace) // skips multiple spaces/tabs
				break;

			iterator[i] = '\0';                     // terminate new substring,
			lexemes.push_back(tokenizer(iterator)); // tokenize it,
			iterator = &iterator[i + 1];            // then reset the base pointer
			break;
		}
	}
}

Lexeme tokenizer(char* name)
{
	size_t len{ strlen(name) };
	if (name[len - 1] == ':') // label
	{
		name[len - 1] = '\0'; // remove the colon at the end
		return Lexeme{ name, name[0] == '.' ? Lexeme::LOCAL_LABEL : Lexeme::LABEL };
	}
	else if (/*check for opcode*/) // opcode
	{
		return Lexeme{ name, Lexeme::OPCODE };
	}
	else if (/*check for reg*/) // register
	{
		if (name[0] == 'r')
			name = &name[1]; // remove optional r
		if (name[2] == ',')
			name[2] = '\0'; // remove optional comma

		return Lexeme{ name, Lexeme::REGISTER };
	}
	else if (/*check for imm*/) // immediate
	{
		return Lexeme{ name, Lexeme::IMMEDIATE };
	}
	else
	{
		return Lexeme{ name, Lexeme::IDENTIFIER };
	}
}
