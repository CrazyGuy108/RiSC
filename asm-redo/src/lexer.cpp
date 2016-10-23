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
		  isKeyword(name)    ? Token::KEYWORD
		: isImmediate(name)  ? Token::IMMEDIATE
		: isRegister(name)   ? Token::REGISTER
		: isIdentifier(name) ? Token::IDENTIFIER
		: isLocalLabel(name) ? Token::LOCAL_LABEL
		: isLabel(name)      ? Token::LABEL
		                     : Token::ERROR };
}

bool Lexer::isKeyword(const char* name)
{
	return false; // placeholder
}

bool Lexer::isImmediate(const char* name)
{
	// ecma regex equivalent:
	// imm = ^(\-)?(0x[0-9|A-F]+)|([0-9]+)\b

	enum State
	{
		A, B, C, D, E, F, G
	};

	static const State states[7][5] // state table
	{
		// 1-9 A-F 0 x -
		{ F, G, B, G, C }, // A
		{ F, G, F, D, G }, // B
		{ F, G, B, G, G }, // C
		{ E, E, E, G, G }, // D
		{ E, E, E, G, G }, // E (accepting state)
		{ F, G, F, G, G }, // F (accepting state)
		{ G, G, G, G, G }, // G (default rejecting state)
	};

	State state{ A };
	size_t i{ 0 };
	while (name[i] != '\0')
	{
		if(name[i] >= '1' && name[i] <= '9')
			state = states[state][0];
		else if(name[i] >= 'A' && name[i] <= 'F')
			state = states[state][1];
		else
		{
			switch (name[i])
			{
			case '0':
				state = states[state][2];
				break;

			case 'x':
				state = states[state][3];
				break;
			case '-':
				state = states[state][4];
				break;
			
			default:
				return false; // outside of state table
			}
		}

		if(state == G)
			return false; // in rejecting state, so shouldn't continue

		++i;
	}

	return state == E || state == F;
}

bool Lexer::isRegister(const char* name)
{
	// ecma regex equivalent:
	// reg = ^r[0-7]\b

	enum State
	{
		A, B, C, D
	};

	static const State states[4][2] // state table
	{
		// r 0-7
		{ B, D }, // A
		{ D, C }, // B
		{ D, D }, // C (accepting state)
		{ D, D }  // D (default rejecting state)
	};

	State state{ A };
	size_t i{ 0 };
	while (name[i] != '\0')
	{
		if(name[i] == 'r')
			state = states[state][0];
		else if(name[i] >= '0' && name[i] <= '7')
			state = states[state][1];
		else
			return false; // outside of state table

		if(state == D) // in rejecting state
			return false;

		++i;
	}

	return state == C;
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
