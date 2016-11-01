#include "../inc/lexer.h"

Lexer::Lexer(const char* program)
	: tokens{}, errors{ 0 }
{
	analyze(program);
}

void Lexer::analyze(const char* program)
{
	static const State states[10][2] // state table
	{
		// letter digit
		{ D, B }, // A (start/space/tab state)
		{ B, B }, // B (immediate accepting state)
		{ D, D }, // C (register accepting state)
		{ D, D }, // D (keyword/identifier accepting state)
		{ G, G }, // E (label accepting state, entered by a ':' while in id state)
		{ A, A }, // F (newline state, entered by a '\n')
		{ G, G }, // G (error accepting state)
		{ H, H }, // H (comment state, entered by a '#')
		{ B, B }, // I (imm digit check, entered by a start-of-word '-')
		{ D, C }  // J (reg digit check, entered by a start-of-word 'r' )
	};

	tokens.emplace("null", Token::BEGIN);

	// lexically parse the program, tokenizing and categorizing matches
	//  by using the state table and some special cases

	Lexeme iterator{ program, program };
	StateTracker state{ START };
	while (iterator.getEnd()[0] != '\0')
	{
		// change states depending on the next character
		switch (iterator.getEnd()[0])
		{
		case '\t':
		case ' ': // space/tab
			if(state.getCurr() != COMMENT)
				state = START;
			break;

		case 'r': // could be register name
			if (state.getCurr() == START)
				state = REG_CHECK;
			else
				state = states[state.getCurr()][0]; // treat as letter
			break;

		case '-': // could be immediate name
			if (state.getCurr() == START)
				state = IMM_CHECK;
			else
			{
				// error: invalid character
				state = ERROR;
				++errors;
			}
			break;

		case ':': // could be label name
			if(state.getCurr() == ID)
				state = LABEL;
			else if(state.getCurr() != COMMENT)
				state = ERROR; // can't have a colon anywhere else
			break;

		case '\n': // newline
			state = NEWLINE;
			break;

		case '#': // line comment
			state = COMMENT;
			break;

		default:
			if (letter(iterator.getEnd()[0]))
				state = states[state.getCurr()][0];
			else if (digit(iterator.getEnd()[0]))
				state = states[state.getCurr()][1]; 
			else
			{
				// error: invalid character
				state = ERROR;
				++errors;
			}
		}

		// decide what to do based on what state it switched to
		if (state.getCurr() != START &&
		    state.getLast() == START) // start of word
		{
			// reset iterator
			iterator.setBeg(iterator.getEnd());
		}
		else if (state.getLast() == COMMENT &&
		         state.getCurr() == NEWLINE) // end of comment
		{
			// reset iterator
			iterator.setBeg(iterator.getEnd());
			tokens.emplace("null", Token::NEWLINE); // terminate the current line
		}
		else if(state.getLast() != START) // end of word (possibly)
		{
			switch (state.getCurr())
			{
			case START: // end of word
				tokenize(iterator, state.getLast()); // tokenize the lexeme
				break;

			case NEWLINE: // end of word and line
				tokenize(iterator, state.getLast()); // tokenize the lexeme
				tokens.emplace("null", Token::NEWLINE); // terminate the current line
				break;
			}
		}

		// advance to the next character
		iterator.setEnd(iterator.getEnd() + 1);
	}

	tokens.emplace("null", Token::END);
}

Token Lexer::next()
{
	if(tokens.empty())
		return Token{ "null", Token::END };
	else
	{
		Token tmp{ tokens.front() };
		tokens.pop();
		return tmp;
	}
}

size_t Lexer::getErrors() const
{
	return errors;
}

bool Lexer::empty() const
{
	return tokens.empty();
}

void Lexer::tokenize(const Lexeme& l, State last)
{
	Token::Type tmp{ parseState(last) };

	if (keywords.find(l) != keywords.end()) // could be a keyword
		tmp = Token::KEYWORD;
	else if (tmp == Token::ERROR) // check for errors
	{
		// error: invalid token
		++errors;
	}

	tokens.emplace(l, tmp); // create the token
}

Token::Type Lexer::parseState(State s)
{
	switch (s)
	{
	case IMM:
		return Token::IMMEDIATE;

	case REG:
		return Token::REGISTER;

	case ID:
		return Token::IDENTIFIER;

	case LABEL:
		return Token::LABEL;

	default: // non-accepting state
		return Token::ERROR;
	}
}

bool Lexer::letter(char c)
{
	// regex: [a-z|A-Z]
	return c >= 'a' && c <= 'z' ||
	       c >= 'A' && c <= 'Z';
}

bool Lexer::digit(char c)
{
	// regex: [0-9]
	return c >= '0' && c <= '9';
}

StateTracker::StateTracker(Lexer::State curr)
	: curr{ curr }, last{ Lexer::START } {}

Lexer::State StateTracker::getCurr() const
{
	return curr;
}

Lexer::State StateTracker::getLast() const
{
	return last;
}

StateTracker& StateTracker::operator=(Lexer::State s)
{
	last = curr;
	curr = s;
	return *this;
}
