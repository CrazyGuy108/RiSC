#ifndef LEXER_H
#define LEXER_H

#include <map>      // for map
#include <vector>   // for vector
#include "lexeme.h" // for Lexeme

#define TOKEN_CHECK(type) bool type ## (const char* name)

// performs lexical analysis on the source code
std::vector<Lexeme> lexer(char* program);

// tokenizes a particular token
Lexeme tokenizer(char* name);

// token name checkers

TOKEN_CHECK(isLabelName);
TOKEN_CHECK(isRegName);
TOKEN_CHECK(isImmName);

// token name formatters

Lexeme::Category label(char* name);
Lexeme::Category reg(char* name);
Lexeme::Category imm(char* name);
Lexeme::Category resolve(char* name);

#endif // LEXER_H
