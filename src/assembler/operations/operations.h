#ifndef OPERATIONS_H
#define OPERATIONS_H

// prototype to resolve circular inclusion

class Line;

// opcodes

Line add(size_t argc, const char** argv);

Line addi(size_t argc, const char** argv);

Line nand(size_t argc, const char** argv);

Line lui(size_t argc, const char** argv);

Line sw(size_t argc, const char** argv);

Line lw(size_t argc, const char** argv);

Line beq(size_t argc, const char** argv);

Line jalr(size_t argc, const char** argv);

// pseudo ops

Line nop(size_t argc, const char** argv);

Line halt(size_t argc, const char** argv);

Line lli(size_t argc, const char** argv);

Line movi(size_t argc, const char** argv);

Line fill(size_t argc, const char** argv);

Line space(size_t argc, const char** argv);

#include "../instruction/instruction.h"

#endif // OPERATIONS_H