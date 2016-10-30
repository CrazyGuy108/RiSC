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

	Lexer(char* iterator);
	
	void analyze(char* iterator); // lexically analyze the given program
	Token next();                 // gets the next lexeme from tokens queue
	size_t getErrors();           // gets the amount of errors the lexer encountered

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

#endif // LEXER_H
