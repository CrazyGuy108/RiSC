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
Lexeme::Category resolve(char* name);

// hand-compiled regex for checking if a given token name is a register name
// that's right, I got the register name check to work...
// ...without regex...
// equivalent: ^(r)?[0-7]{1}(,)?\b
bool isRegName(char* name);

#endif // LEXER_H
