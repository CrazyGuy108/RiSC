#ifndef LEXER_HPP
#define LEXER_HPP

#include <queue>       // for queue
#include "token.hpp"   // for Token
#include "utility.hpp" // for keywords and keyword_map

// state machine that lexically parses a program line by line
class Lexer
{
public:
	enum State
	{
		START,
		IMM,
		REG,
		ID,
		LABEL,
		NEWLINE,
		ERROR,
		COMMENT,
		IMM_CHECK,
		REG_CHECK,
		A = START, B, C, D, E, F, G, H, I, J
	};

	enum Column
	{
		LETTER, DIGIT
	};

	Lexer(const char* program);
	
	void analyze(const char* program); // lexically analyze the given program

	Token next();             // gets the next lexeme from tokens queue
	size_t getErrors() const; // gets the amount of errors the lexer encountered
	bool empty() const;       // checks if the lexer is all out of tokens

private:
	// helpers

	// creates a token out of the given string
	// the given state s tells it how it should treat the token
	void tokenize(const Lexeme& l, State last);

	// static helpers

	static Token::Type parseState(State s);
	static bool letter(char c);
	static bool digit(char c);

	size_t errors;            // tracks the amount of errors the lexer encountered
	std::queue<Token> tokens; // queue containing the Tokens created by constructor
};

// keeps track of the machine's state and the state it just exited
class StateTracker
{
public:
	StateTracker(Lexer::State curr); // initializes state

	Lexer::State getCurr() const;            // gets current state
	Lexer::State getLast() const;            // gets last state
	StateTracker& operator=(Lexer::State s); // sets current state and last state

private:
	Lexer::State curr; // current state
	Lexer::State last; // last state
};

#endif // LEXER_HPP
