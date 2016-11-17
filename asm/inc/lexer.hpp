#ifndef LEXER_HPP
#define LEXER_HPP

#include <queue>       // for queue
#include "token.hpp"   // for Token
#include "utility.hpp" // for keywords and keyword_map

// state machine that lexically parses a program line by line
class Lexer
{
public:
	Lexer(const char* program);
	
	void analyze(const char* program); // lexically analyze the given program

	Token next();             // gets the next lexeme from tokens queue
	size_t getErrors() const; // gets the amount of errors the lexer encountered
	bool empty() const;       // checks if the lexer is all out of tokens

private:
	enum State;
	enum Column;
	class StateTracker;

	// creates a token out of the given Lexeme
	// the given state tells it how it should tokenize it
	void tokenize(const Lexeme& l, State last);

	// static helpers

	static Token::Type parseState(State s);
	static bool letter(char c);
	static bool digit(char c);

	size_t errors;            // tracks the amount of errors the lexer encountered
	std::queue<Token> tokens; // queue containing the Tokens created by constructor
};

enum Lexer::State
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
	A = 0, B, C, D, E, F, G, H, I, J
};

enum Lexer::Column
{
	LETTER, DIGIT
};

// keeps track of the machine's state and the state it just exited
class Lexer::StateTracker
{
public:
	StateTracker(State curr); // initializes state

	State getCurr() const;            // gets current state
	State getLast() const;            // gets last state
	StateTracker& operator=(State s); // sets current state and last state

private:
	State curr; // current state
	State last; // last state
};

#endif // LEXER_HPP
