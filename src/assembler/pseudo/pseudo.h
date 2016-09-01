#ifndef PSEUDO_H
#define PSEUDO_H

class Line;

// function pointer typedef for the functions below
typedef Line(*Pseudo)(size_t argc, const char** argv);

Line nop(size_t argc, const char** argv);

Line halt(size_t argc, const char** argv);

Line lli(size_t argc, const char** argv);

Line movi(size_t argc, const char** argv);

Line fill(size_t argc, const char** argv);

Line space(size_t argc, const char** argv);

#include "../instruction/instruction.h"

#endif // PSEUDO_H