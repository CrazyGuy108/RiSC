#ifndef LEXER_H
#define LEXER_H

#include <queue>    // for queue
#include <vector>   // for vector
#include "lexeme.h" // for Lexeme

// state machine that lexically parses a program line by line
class Lexer
{
public:
	Lexer(char* iterator);
	
	Lexeme next(); // tokenizes the next lexeme

private:
	// creates a Lexeme of a token name
	static Lexeme tokenize(char* name);
	
	// token name checkers
	
	static bool isLabelName(const char* name);
	static bool isRegName(const char* name);
	static bool isImmName(const char* name);
	
	// token name formatters
	
	static Lexeme::Category formatLabel(char* name);
	static Lexeme::Category formatReg(char* name);
	static Lexeme::Category formatImm(char* name);
	static Lexeme::Category formatKeyword(char* name);
	
	char* iterator; // pointer that iterates through the program
	size_t index;   // index of the character relative to iterator currently being analyzed

	bool end;       // found end of program
	bool space;     // found a space/tab
	bool comment;   // found a comment

	std::queue<Lexeme> lexemes; // queue containing the Lexemes created by constructor
};

#endif // LEXER_H
