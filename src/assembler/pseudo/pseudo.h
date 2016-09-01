#ifndef PSEUDO_H
#define PSEUDO_H

class Line;

// function pointer typedef for the functions below
typedef void(*Pseudo)(Line* thisptr, size_t argc, const char** argv);

void nop(Line* thisptr, size_t argc, const char** argv);

void halt(Line* thisptr, size_t argc, const char** argv);

void lli(Line* thisptr, size_t argc, const char** argv);

void movi(Line* thisptr, size_t argc, const char** argv);

void fill(Line* thisptr, size_t argc, const char** argv);

void space(Line* thisptr, size_t argc, const char** argv);

#include "../instruction/instruction.h"

#endif // PSEUDO_H