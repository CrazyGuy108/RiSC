#ifndef PSEUDO_H
#define PSEUDO_H

class Line;

// function pointer typedef for the functions below
typedef void(*Pseudo)(size_t argc, const char** argv);

void nop(size_t argc, const char** argv);

void halt(size_t argc, const char** argv);

void lli(size_t argc, const char** argv);

void movi(size_t argc, const char** argv);

void fill(size_t argc, const char** argv);

void space(size_t argc, const char** argv);

#include "../instruction/instruction.h"

#endif // PSEUDO_H