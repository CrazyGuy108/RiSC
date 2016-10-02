#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>  // for ifstream and ostream
#include <iostream> // for cout
#include <vector>   // for vector
#include "parse.h"  // for compile()

// preprocessor for assembler
// resolves directives and labels similar to the C preprocessor
std::vector<OP((*))> preprocess(char* program);

void assemble(int argc, char** argv);

#endif // ASSEMBLER_H