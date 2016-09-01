#ifndef OPCODE_H
#define OPCODE_H

class Line;

typedef Line(*Op)(size_t argc, const char** argv);

#include "../instruction/instruction.h"

Line add(size_t argc, const char** argv);

Line addi(size_t argc, const char** argv);

Line nand(size_t argc, const char** argv);

Line lui(size_t argc, const char** argv);

Line sw(size_t argc, const char** argv);

Line lw(size_t argc, const char** argv);

Line beq(size_t argc, const char** argv);

Line jalr(size_t argc, const char** argv);

#endif // OPCODE_H