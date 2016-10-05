#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>      // for ifstream and ostream
#include <iostream>     // for cout
#include <vector>       // for vector
#include "operations.h" // for Opcode
#include "parse.h"      // for compile()

// enables debug messages
//#define DEBUG

size_t preprocessor(std::vector<std::vector<char*>>& words, std::vector<Opcode>& opcodes, char* iterator);

size_t compiler(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes, line_t& bytecode);

void assemble(int argc, char** argv);

#endif // ASSEMBLER_H