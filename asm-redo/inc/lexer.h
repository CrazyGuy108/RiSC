#ifndef LEXER_H
#define LEXER_H

#include <set>     // for set
#include <queue>   // for queue
#include "token.h" // for Token

// state machine that lexically parses a program line by line
class Lexer
{
public:
	enum State
	{
		A, B, C, D, E, F, G, H, I, J,
		START = A,
		IMM_ACCEPT,
		REG_ACCEPT,
		ID_ACCEPT,
		LABEL_ACCEPT,
		NEWLINE_ACCEPT,
		ERROR_ACCEPT,
		COMMENT,
		IMM_CHECK,
		REG_CHECK
	};

	Lexer(char* iterator);
	
	void analyze(char* iterator); // lexically analyze the given program
	Token next();                 // gets the next lexeme from tokens queue

private:
	// creates a Lexeme of a token name
	static Token tokenize(char* name);

	// state machines

	static bool isKeyword(const char* name);
	static bool isImmediate(const char* name);
	static bool isRegister(const char* name);
	static bool isIdentifier(const char* name);
	static bool isLabel(const char* name);

	// state machine helpers

	static bool letter(char c);
	static bool digit(char c);

	std::queue<Token> tokens; // queue containing the Tokens created by constructor
};

#endif // LEXER_H
