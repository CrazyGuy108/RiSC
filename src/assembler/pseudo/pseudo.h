#ifndef PSEUDO_H
#define PSEUDO_H

class Line;

Line nop(size_t argc, const char** argv);

Line halt(size_t argc, const char** argv);

Line lli(size_t argc, const char** argv);

Line movi(size_t argc, const char** argv);

Line fill(size_t argc, const char** argv);

Line space(size_t argc, const char** argv);

#include "../instruction/instruction.h"

#endif // PSEUDO_H