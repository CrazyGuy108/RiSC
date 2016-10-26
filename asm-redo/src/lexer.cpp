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
			break;

		case '-': // could be immediate name
			if (state.getCurr() == START)
				state = IMM_CHECK;
			break;

		case ':': // could be label name
			if(state.getCurr() == ID)
				state = LABEL;
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
			}
		}

		if (state.getCurr() != START && state.getLast() == START) // start of word
		{
			// reset iterator
			iterator = &iterator[i];
			i = 1;
		}
		else if (state.getCurr() == START && state.getLast() != START) // end of word
		{
			// create token if in accepting state
		}
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

Token Lexer::tokenize(char* name)
{
	return Token{ name,
		  isKeyword(name)    ? Token::KEYWORD
		: isImmediate(name)  ? Token::IMMEDIATE
		: isRegister(name)   ? Token::REGISTER
		: isIdentifier(name) ? Token::IDENTIFIER
		: isLabel(name)      ? Token::LABEL
		                     : Token::ERROR };
}

bool Lexer::isKeyword(const char* name)
{
	class StrLess
	{
	public:
		bool operator()(const char* a, const char* b) const
		{
			return strcmp(a, b) < 0;
		}
	};

	static const std::set<const char*, StrLess> keywords
	{
		"add", "addi", "nand", "lui", "sw", "lw", "beq", "jalr"
	};

	return keywords.find(name) != keywords.end();
}

bool Lexer::isImmediate(const char* name)
{
	// regex: (\-)?('0x'[digit|A-F]+)|([digit]+)

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
	// regex: 'r'[0-7]

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
	// regex: [letter][letter|digit]*

	static const State states[3][2] // state table
	{
		// letter digit
		{ B, C }, // A
		{ B, B }, // B (accepting state)
		{ C, C }  // C (default rejecting state)
	};

	State state{ A };
	size_t i{ 0 };
	while (name[i] != '\0')
	{
		if(letter(name[i]))
		   state = states[state][0];
		else if(digit(name[i]))
			state = states[state][1];
		else
			return false; // outside of state table

		if(state == C) // in rejecting state
			return false;
	}

	return state == B;
}

bool Lexer::isLabel(const char* name)
{
	// regex: [letter][letter|digit]*':'

	static const State states[4][3]
	{
		// letter digit ':'
		{ B, D, D }, // A
		{ B, B, C }, // B
		{ D, D, D }, // C (accepting state)
		{ D, D, D }  // D (default rejecting state)
	};

	State state{ A };
	size_t i{ 0 };
	while (name[i] != '\0')
	{
		if(letter(name[i]))
			state = states[state][0];
		else if(digit(name[i]))
			state = states[state][1];
		else if(name[i] == ':')
			state = states[state][2];
		else
			return false; // outside of state table

		if(state == D) // in rejecting state
			return false;

		++i;
	}

	return state == C;
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
