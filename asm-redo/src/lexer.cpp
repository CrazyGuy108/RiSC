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

bool Lexer::isKeyword(const char* name)
{
	return false; // placeholder
}

bool Lexer::isImmediate(const char* name)
{
	// ecma regex equivalent:
	// imm = ^(0x)?[0-9]+\b

	static const size_t states[5][3] // state table
	{
		// 0 1-9 x
		{ 2, 1, 4 }, // A
		{ 1, 1, 4 }, // B (accepting state)
		{ 1, 1, 3 }, // C
		{ 1, 1, 4 }, // D
		{ 4, 4, 4 }  // E
	};

	size_t state{ 0 };
	size_t i{ 0 };
	while (name[i] != '\0')
	{
		if(name[i] == '0')
			state = states[state][0];
		else if(name[i] >= '1' && name[i] <= '9')
			state = states[state][1];
		else if(name[i] == 'x')
			state = states[state][2];
		else
			return false; // outside of state table

		++i;
	}

	return state == 1;
}

bool Lexer::isRegister(const char* name)
{
	return false; // placeholder
}

bool Lexer::isIdentifier(const char* name)
{
	return false; // placeholder
}

bool Lexer::isLocalLabel(const char* name)
{
	return false; // placeholder
}

bool Lexer::isLabel(const char* name)
{
	return false; // placeholder
}
