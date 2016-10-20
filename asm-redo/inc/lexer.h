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

#endif // LEXER_H
