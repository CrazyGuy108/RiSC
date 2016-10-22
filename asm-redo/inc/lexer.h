#ifndef LEXER_H
#define LEXER_H

#include <queue>   // for queue
#include <vector>  // for vector
#include "token.h" // for Token

// state machine that lexically parses a program line by line
class Lexer
{
public:
	Lexer(char* iterator);
	
	Token next(); // gets the next lexeme

private:
	// creates a Lexeme of a token name
	static Token tokenize(char* name);
	
	// token name checkers
	
	static bool isLabelName(const char* name);
	static bool isRegName(const char* name);
	static bool isImmName(const char* name);
	
	// token name formatters
	
	static Token::Category formatLabel(char* name);
	static Token::Category formatReg(char* name);
	static Token::Category formatImm(char* name);
	static Token::Category formatKeyword(char* name);

	std::queue<Token> tokens; // queue containing the Tokens created by constructor
};

#endif // LEXER_H
