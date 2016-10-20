#ifndef LEXER_H
#define LEXER_H

#include <map>      // for map
#include <vector>   // for vector
#include "lexeme.h" // for Lexeme

// performs lexical analysis on the source code
std::vector<Lexeme> lexer(char* program);

// tokenizes a particular token
Lexeme tokenizer(char* name);

// resolves a token into either a reserved word/opcode or an identifier
Lexeme::Category resolve(const char* name);

// checks if the given token is an immediate
bool isImmName(const char* name);

// checks if the given token is a register and formats it
// regex equivalent (without formatting the input): ^(r)?[0-7]{1}(,)?\b
bool isRegName(char* name);

// checks if the given token is a label and formats it
bool isLabelName(char* name);

#endif // LEXER_H
