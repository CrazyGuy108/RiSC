#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>      // for ifstream and ostream
#include <iostream>     // for cout
#include <vector>       // for vector
#include "operations.h" // for Opcode
#include "parse.h"      // for compile()

void preprocess(std::vector<std::vector<char*>>& words, std::vector<Opcode>& opcodes, char* iterator);

void assemble(int argc, char** argv);

#endif // ASSEMBLER_H