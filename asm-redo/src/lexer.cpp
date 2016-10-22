#include "../inc/lexer.h"

Lexer::Lexer(char* iterator)
	: tokens{}
{
	size_t index{ 0 }; // index of current character relative to iterator

	bool space{ true };    // found a space/tab
	bool comment{ false }; // found a comment

	tokens.emplace(nullptr, Token::BEGIN); // begin

	while (iterator[index] != '\0')
	{
		switch (iterator[index])
		{
		case '\n': // newline
			if(!space && !comment) // act as if a space just happened
			{
				iterator[index] = '\0'; // terminate substring
				tokens.emplace(tokenize(iterator)); // tokenize and add as a Lexeme
			}

			space = true;    // allow spaces before the next token
			comment = false; // terminate comment (if there was one)

			tokens.emplace(nullptr, Token::NEWLINE); // terminate line

			// reset iterator and index
			iterator = &iterator[index + 1];
			index = 0;
			break;

		case ' ':  // space
		case '\t': // tab
			if (!space && !comment) // ignore comments/multiple spaces
			{
				space = true; // just found a space

				iterator[index] = '\0'; // terminate substring
				tokens.emplace(tokenize(iterator)); // tokenize and add as a Lexeme
			}

			// reset iterator and index
			iterator = &iterator[index + 1];
			index = 0;
			break;

		case '#': // comment
			comment = true;
			++index;
			break;

		default: // nonspecial character
			space = false;
			++index;
		}
	}

	tokens.emplace(nullptr, Token::END); // end
}

Token Lexer::next()
{
	if(tokens.empty())
		return Token{ nullptr, Token::END };
	else
	{
		Token tmp{ tokens.front() };
		tokens.pop();
		return tmp;
	}
}

Token Lexer::tokenize(char* name)
{
	return Token{ name,
		isLabelName(name) ? formatLabel(name)
		: isRegName(name) ? formatReg(name)
		: isImmName(name) ? formatImm(name)
		                  : formatKeyword(name) };
}

bool Lexer::isLabelName(const char* name)
{
	return name[strlen(name) - 1] == ':';
}

bool Lexer::isRegName(const char* name)
{
	// BEHOLD the almighty unmaintainable short-circuit evaluation behemoth!
	// now with spaces and comments so it doesn't hurt your eyes as much
	size_t len{ strlen(name) };
	return (len == 1 &&          // digit start
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
	         name[2] == ','));   // r+digit+comma end
}

bool Lexer::isImmName(const char* name)
{
	size_t len{ strlen(name) };
	return (len >= 1 && // digit start
	        (name[0] >= '0' &&
	         name[0] <= '9')) || // digit end
	       (len >= 2 && // sign+digit start
	        (name[0] == '-' &&
	         name[1] >= '0' &&
	         name[2] <= '9')); // sign+digit end
}

Token::Category Lexer::formatLabel(char* name)
{
	name[strlen(name) - 1] = '\0'; // remove colon
	return name[0] == '.' ? Token::LOCAL_LABEL
	                      : Token::LABEL;
}

Token::Category Lexer::formatReg(char* name)
{
	if (name[0] == 'r') // remove optional r
	{
		name[0] = name[1];
		name[1] = '\0'; // implicitly also ignores the comma
	}
	else if (name[1] == ',') // remove optional comma
		name[1] = '\0';
	
	return Token::REGISTER;
}

Token::Category Lexer::formatImm(char* name)
{
	return Token::IMMEDIATE;
}

Token::Category Lexer::formatKeyword(char* name)
{
	return !strcmp(name, "add")  ? Token::ADD
	     : !strcmp(name, "addi") ? Token::ADDI
	     : !strcmp(name, "nand") ? Token::NAND
	     : !strcmp(name, "lui")  ? Token::LUI
	     : !strcmp(name, "sw")   ? Token::SW
	     : !strcmp(name, "lw")   ? Token::LW
	     : !strcmp(name, "beq")  ? Token::BEQ
	     : !strcmp(name, "jalr") ? Token::JALR
	                             : Token::IDENTIFIER;
}
