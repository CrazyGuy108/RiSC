#ifndef LEXER_H
#define LEXER_H

#include <map>      // for map
#include <vector>   // for vector
#include "lexeme.h" // for Lexeme

#define TOKEN_CHECK(type) bool type ## (const char* name)
#define TOKEN_FORMAT(type) Lexeme::Category type ## (char* name)

// performs lexical analysis on the source code
std::vector<Lexeme> lexer(char* program);

// tokenizes a particular token
Lexeme tokenizer(char* name);

// token name checkers

TOKEN_CHECK(isLabelName);
TOKEN_CHECK(isRegName);
TOKEN_CHECK(isImmName);

// token name formatters

TOKEN_FORMAT(label);
TOKEN_FORMAT(reg);
TOKEN_FORMAT(imm);
TOKEN_FORMAT(resolve);

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
	
	static TOKEN_CHECK(isLabelName);
	static TOKEN_CHECK(isRegName);
	static TOKEN_CHECK(isImmName);
	
	// token name formatters
	
	static TOKEN_FORMAT(formatLabel);
	static TOKEN_FORMAT(formatReg);
	static TOKEN_FORMAT(formatImm);
	static TOKEN_FORMAT(formatKeyword);
	
	char* iterator; // pointer that iterates through the program
	size_t index;   // index of the character relative to iterator currently being analyzed
	bool end;       // this will be true if the lexer has reached the end of the program
};

#endif // LEXER_H
