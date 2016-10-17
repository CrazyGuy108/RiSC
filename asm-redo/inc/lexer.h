#ifndef LEXER_H
#define LEXER_H

#include <vector>   // for vector
#include "lexeme.h" // for Lexeme

// performs lexical analysis on the source code
std::vector<Lexeme> lexer(char* program);

// tokenizes a particular token
Lexeme tokenizer(char* name);

#endif // LEXER_H
