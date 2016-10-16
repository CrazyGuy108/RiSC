#ifndef EMULATOR_H
#define EMULATOR_H

#include <iostream>    // for cout
#include "risc.h"      // for RiSC
#include "utilities.h" // for opcode constants

void emulator(char* contents, size_t length);

#endif // EMULATOR_H