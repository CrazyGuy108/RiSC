#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <cstdint>

// prototype to resolve circular inclusion

class Line;

// opcodes

Line add(size_t argc, const char** argv, uint16_t line);

Line addi(size_t argc, const char** argv, uint16_t line);

Line nand(size_t argc, const char** argv, uint16_t line);

Line lui(size_t argc, const char** argv, uint16_t line);

Line sw(size_t argc, const char** argv, uint16_t line);

Line lw(size_t argc, const char** argv, uint16_t line);

Line beq(size_t argc, const char** argv, uint16_t line);

Line jalr(size_t argc, const char** argv, uint16_t line);

// pseudo ops

Line nop(size_t argc, const char** argv, uint16_t line);

Line halt(size_t argc, const char** argv, uint16_t line);

Line lli(size_t argc, const char** argv, uint16_t line);

Line movi(size_t argc, const char** argv, uint16_t line);

Line fill(size_t argc, const char** argv, uint16_t line);

Line space(size_t argc, const char** argv, uint16_t line);

#include "../instruction/instruction.h"

#endif // OPERATIONS_H