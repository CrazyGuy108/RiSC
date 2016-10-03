#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>  // for ifstream and ostream
#include <iostream> // for cout
#include <vector>   // for vector
#include "parse.h"  // for compile()

void preprocess(std::vector<std::vector<char*>>& words, std::vector<OP((*))>& opcodes, char* iterator);

void assemble(int argc, char** argv);

#endif // ASSEMBLER_H