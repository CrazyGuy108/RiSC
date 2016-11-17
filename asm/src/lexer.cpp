#include "../inc/lexer.hpp"

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
			else // treat as letter
				state = states[state.getCurr()][LETTER];
			break;

		case '-': // could be immediate name
			if (state.getCurr() == START)
				state = IMM_CHECK;
			else if (state.getCurr() != COMMENT)
				state = ERROR; // can't have a hyphen anywhere else
			break;

		case ':': // could be label name
			if (state.getCurr() == ID)
				state = LABEL;
			else if (state.getCurr() != COMMENT)
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
				state = states[state.getCurr()][LETTER];
			else if (digit(iterator.getEnd()[0]))
				state = states[state.getCurr()][DIGIT]; 
			else if (state.getCurr() != COMMENT)
			{
				std::cout << "error: invalid character '" << iterator.getEnd()[0] << "'\n";
				state = ERROR;
				++errors;
			}
		}

		// decide what to do based on what state it switched to
		if (state.getCurr() == START || // end of word
		    state.getCurr() == NEWLINE) // end of the line
		{
			switch (state.getLast()) // what just happened before?
			{
			case START:   // trailing spaces after a line of code, typical
			case NEWLINE: // next line of code separated by multiple lines
			case COMMENT: // terminating a line comment
				break; // exclude these cases from creating a token

			default: // assumed to be in an accepting/error state
				// create the appropriate token
				tokenize(iterator, state.getLast());
			}

			// terminate the current line if needed
			if(state.getCurr() == NEWLINE)
				tokens.emplace(Token::NEWLINE);

			// reset iterator and state
			iterator.setBeg(iterator.getEnd() + 1);
			state = START;
		}
		else if (state.getLast() == START) // start of word
			iterator.setBeg(iterator.getEnd()); // reset iterator

		// advance to the next character
		iterator.setEnd(iterator.getEnd() + 1);
	}
}

Token Lexer::next()
{
	if(tokens.empty())
		return Token{ Token::ERROR };
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
	Lexeme lexeme{ l };

	if (tmp == Token::ERROR) // check for errors
	{
		std::cout << "error: invalid token \"" << l << "\"\n";
		++errors;
	}
	else if(tmp == Token::LABEL) // remove colon from label declaration
		lexeme.setEnd(lexeme.getEnd() - 1);
	else // could be an opcode
	{
		opcode_map::const_iterator it{ opcodes.find(lexeme) };
		if(it != opcodes.cend())
			tmp = it->second;
	}

	tokens.emplace(lexeme, tmp); // create the token
}

Token::Type Lexer::parseState(State s)
{
	switch (s)
	{
	case REG:
		return Token::REGISTER;

	case IMM:
		return Token::IMMEDIATE;

	case REG_CHECK: // couldn't resolve as a register, so likely a keyword/identifier
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

Lexer::StateTracker::StateTracker(Lexer::State curr)
	: curr{ curr }, last{ Lexer::START } {}

Lexer::State Lexer::StateTracker::getCurr() const
{
	return curr;
}

Lexer::State Lexer::StateTracker::getLast() const
{
	return last;
}

Lexer::StateTracker& Lexer::StateTracker::operator=(Lexer::State s)
{
	last = curr;
	curr = s;
	return *this;
}
