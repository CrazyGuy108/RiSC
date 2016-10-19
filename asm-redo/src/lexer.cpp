#include "../inc/lexer.h"

std::vector<Lexeme> lexer(char* program)
{
	std::vector<Lexeme> lexemes; // keeps track of all the Lexemes the lexer creates
	bool foundSpace{ true };     // if the lexer has found a space, this will be true
	bool foundComment{ false };  // if the lexer has found a comment, this will be true

	// iterate through characters
	size_t i{ 0 };
	while (program[i] != '\0')
	{
		switch (program[i])
		{
		case '\n': // new line
			if (!(foundComment || foundSpace)) // tokenize last word
			{
				program[i] = '\0';
				lexemes.push_back(tokenizer(program));
			}

			foundComment = false; // terminate comment
			foundSpace = true;    // allows ignoring space/tab from beginning of line
			lexemes.push_back(Lexeme{ nullptr, Lexeme::NEWLINE }); // basically semicolon insertion here
			program = &program[i + 1]; // reset the base pointer
			i = 0; // reset iterator
			break;

		case ' ': // space/tab means a new word
		case '\t':
			if (foundSpace || foundComment) // skips comments and multiple spaces/tabs
				break;

			foundSpace = true;                     // just found a space
			program[i] = '\0';                     // terminate new substring,
			lexemes.push_back(tokenizer(program)); // tokenize it,
			program = &program[i + 1];             // then reset the base pointer
			i = 0;                                 // and the iterator
			break;

		case '#': // comment
			foundComment = true;
			++i;
			break;

		default: // nonspecial character, probably part of an identifier/word
			foundSpace = false;
			++i;
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
	else if (isRegName(name)) // register
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
	else // either reserved word/opcode or identifier
	{
		return Lexeme{ name, resolve(name) };
	}
}

Lexeme::Category resolve(char* name)
{
	return !strcmp(name, "add")  ? Lexeme::ADD
	     : !strcmp(name, "addi") ? Lexeme::ADDI
	     : !strcmp(name, "nand") ? Lexeme::NAND
	     : !strcmp(name, "lui")  ? Lexeme::LUI
	     : !strcmp(name, "sw")   ? Lexeme::SW
	     : !strcmp(name, "lw")   ? Lexeme::LW
	     : !strcmp(name, "beq")  ? Lexeme::BEQ
	     : !strcmp(name, "jalr") ? Lexeme::JALR
	                             : Lexeme::IDENTIFIER;
}

bool isImmName(char* name)
{
	size_t len{ strlen(name) };
	return (len >= 1 && // digit start
	        (name[0] >= '0' &&
	         name[0] <='9')) || // digit end
	       (len >= 2 && // sign+digit start
	        (name[0] == '-' &&
	         name[1] >= '0' &&
	         name[2] <= '9')); // sign+digit end
}

bool isRegName(char* name)
{
	// BEHOLD the almighty unmaintainable short-circuit evaluation behemoth!
	// now with spaces and comments so it doesn't hurt your eyes as much
	size_t len{ strlen(name) };
	if ((len == 1 &&          // digit start
	     (name[0] >= '0' &&
	      name[0] <= '7')) || // digit end
	    (len == 2 &&          // r+digit start or digit+comma start
	     (name[0] == 'r' &&
	      name[1] >= '0' &&
	      name[1] <= '7') ||  // r+digit end
	     (name[0] >= '0' &&
	      name[0] <= '7' &&
	      name[1] == ',')) || // digit+comma end
	    (len == 3 &&          // r+digit+comma start
	     (name[0] == 'r' &&
	      name[1] >= '0' &&
	      name[1] <= '7' &&
	      name[2] == ',')))   // r+digit+comma end
	{
		// remove optional r
		if (name[0] == 'r')
			name = &name[1];
		
		// remove optional comma
		if(len == 2 && name[1] == ',')
			name[1] = '\0';
		else if (len == 3 && name[2] == ',')
			name[2] = '\0';
		
		return true;
	}
	else
		return false;
}
