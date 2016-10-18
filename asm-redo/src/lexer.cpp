#include "../inc/lexer.h"

std::vector<Lexeme> lexer(char* program)
{
	std::vector<Lexeme> lexemes; // keeps track of all the Lexemes the lexer creates
	bool foundSpace{ true };     // if the lexer has found a space, this will be true
	bool foundComment{ false };  // if the lexer has found a comment, this will be true

	// iterate through characters
	for (size_t i{ 0 }; program[i] != '\0'; ++i)
	{
		switch (program[i])
		{
		case ' ': // space/tab means a new word
		case '\t':
			if (foundSpace) // skips multiple spaces/tabs
				break;

			foundSpace = true;                     // just found a space
			program[i] = '\0';                     // terminate new substring,
			lexemes.push_back(tokenizer(program)); // tokenize it,
			program = &program[i + 1];             // then reset the base pointer
			break;

		case '#': // comment
			foundComment = true;
			break;

		default: // nonspecial character, probably part of an identifier/word
			foundSpace = false;
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
	else if ((len == 1 && // digit start
	          (name[0] >= '0' &&
	           name[0] <= '7')) || // digit end
	         (len == 2 && // r+digit start or digit+comma start
	          (name[0] == 'r' &&
	           name[1] >= '0' &&
	           name[1] <= '7') || // r+digit end
	          (name[0] >= '0' &&
	           name[0] <= '7' &&
	           name[1] == ',')) || // digit+comma end
	         (len == 3 && // r+digit+comma start
	          (name[0] == 'r' &&
	           name[1] >= '0' &&
	           name[1] <= '7' &&
	           name[2] == ',')) // r+digit+comma end
	        ) // register
	{
		// that's right, I got the register name check to work...
		// ...without regex...
		// equivalent: ^(r)?[0-7]{1}(,)?\b

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
