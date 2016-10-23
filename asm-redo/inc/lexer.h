#ifndef LEXER_H
#define LEXER_H

#include <set>     // for set
#include <queue>   // for queue
#include "token.h" // for Token

// state machine that lexically parses a program line by line
class Lexer
{
public:
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
