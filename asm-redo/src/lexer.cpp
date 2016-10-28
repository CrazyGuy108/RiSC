#include "../inc/lexer.h"

Lexer::Lexer(char* iterator)
	: tokens{}, errors{ 0 }
{
	analyze(iterator);
}

void Lexer::analyze(char* iterator)
{
	// keeps track of state and the state it just exited
	class StateTracker
	{
	public:
		StateTracker(State curr) // initializes state
			: curr{ curr }, last{ START } {};

		State getCurr() const // gets current state
		{
			return curr;
		}

		State getLast() const // gets last state
		{
			return last;
		}

		StateTracker& operator=(State s) // sets current state and last state
		{
			last = curr;
			curr = s;
			return *this;
		}

	private:
		State curr; // current state
		State last; // last state
	};

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

	tokens.emplace(nullptr, Token::BEGIN);

	// state machine stuff here, combining everything in tokenize()
	//  as well as some other special functions

	StateTracker state{ START };
	size_t i{ 0 };
	while (iterator[i] != '\0')
	{
		switch (iterator[i])
		{
		case '\t':
		case ' ': // space/tab
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
				state = states[state.getCurr()][0]; // treat as letter
			break;

		case ':': // could be label name
			if(state.getCurr() == ID)
				state = LABEL;
			else
				state = ERROR; // can't have a colon anywhere else
			break;

		case '\n': // newline
			state = NEWLINE;
			break;

		case '#': // line comment
			state = COMMENT;
			break;

		default:
			if (letter(iterator[i]))
				state = states[state.getCurr()][0];
			else if (digit(iterator[i]))
				state = states[state.getCurr()][1]; 
			else
			{
				// error: invalid character
				state = ERROR;
				++errors;
			}
		}

		if (state.getCurr() != START && state.getLast() == START) // start of word
		{
			// reset iterator
			iterator = &iterator[i];
			i = 0;
		}
		else if (state.getCurr() == START || state.getCurr() == NEWLINE && state.getLast() != START) // end of word
		{
			Token::Type tmp{ parseState(state.getLast()) };
			if (tmp == Token::ERROR)
			{
				// error: invalid token
				++errors;
			}

			iterator[i] = '\0'; // terminate lexeme
			tokens.emplace(iterator, tmp); // tokenize the lexeme

			if(state.getCurr() == NEWLINE)
				tokens.emplace(nullptr, Token::NEWLINE); // terminate the current line
		}

		++i;
	}

	tokens.emplace(nullptr, Token::END);
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

size_t Lexer::getErrors()
{
	return errors;
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
