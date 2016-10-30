#ifndef LEXER_H
#define LEXER_H

#include <queue>     // for queue
#include "token.h"   // for Token
#include "utility.h" // for keywords and keyword_map

// state machine that lexically parses a program line by line
class Lexer
{
public:
	enum State
	{
		A, B, C, D, E, F, G, H, I, J,
		START = A,
		IMM,
		REG,
		ID,
		LABEL,
		NEWLINE,
		ERROR,
		COMMENT,
		IMM_CHECK,
		REG_CHECK
	};

	Lexer(const char* program);
	
	void analyze(const char* program); // lexically analyze the given program

	Token next();       // gets the next lexeme from tokens queue
	size_t getErrors(); // gets the amount of errors the lexer encountered

private:
	// helpers

	// creates a token out of the given string
	// the given state s tells it how it should treat the token
	void tokenize(char* name, size_t len, State last);

	// static helpers

	static Token::Type parseState(State s);
	static bool letter(char c);
	static bool digit(char c);

	size_t errors;            // tracks the amount of errors the lexer encountered
	std::queue<Token> tokens; // queue containing the Tokens created by constructor
};

// keeps track of state and the state it just exited
class StateTracker
{
public:
	StateTracker(Lexer::State curr) // initializes state
		: curr{ curr }, last{ Lexer::START } {};

	Lexer::State getCurr() const // gets current state
	{
		return curr;
	}

	Lexer::State getLast() const // gets last state
	{
		return last;
	}

	StateTracker& operator=(Lexer::State s) // sets current state and last state
	{
		last = curr;
		curr = s;
		return *this;
	}

private:
	Lexer::State curr; // current state
	Lexer::State last; // last state
};

#endif // LEXER_H
