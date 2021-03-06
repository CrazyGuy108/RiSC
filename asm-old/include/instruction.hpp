#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "utilities.hpp" // for shift/mask constants

inst_t rrr(inst_t opcode, inst_t regA, inst_t regB, inst_t regC);
inst_t rri(inst_t opcode, inst_t regA, inst_t regB, inst_t immC);
inst_t ri(inst_t opcode, inst_t regA, inst_t immB);

#endif // INSTRUCTION_HPP
