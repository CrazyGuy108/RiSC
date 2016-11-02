#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <fstream>        // for ifstream and ostream
#include <iostream>       // for cout
#include <vector>         // for vector
#include "operations.hpp" // for Opcode
#include "parse.hpp"      // for compile()

// enables debug messages
//#define DEBUG

size_t preprocessor(std::vector<std::vector<char*>>& words, std::vector<Opcode>& opcodes, char* iterator);

size_t compiler(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes, line_t& bytecode);

void assemble(std::ifstream& ifile, std::ostream& ofile);

#endif // ASSEMBLER_HPP
