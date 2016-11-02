#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "instruction.hpp" // for rrr/rri/ri
#include "parse.hpp"       // for reg()/imm()
#include "utilities.hpp"   // for macros/constants

class Opcode
{
public:
	Opcode(OP((*func)), inst_t len);

	OP((*getFunc()  const));
	inst_t length() const;

private:
	OP((*func)); // opcode function to call
	inst_t len;  // amount of instruction words it will take
};

// opcodes

OP(add);
OP(addi);
OP(nand);
OP(lui);
OP(sw);
OP(lw);
OP(beq);
OP(jalr);

// pseudo ops

OP(nop);
OP(halt);
OP(lli);
OP(movi);

// default op

OP(unknown);

#endif // OPERATIONS_HPP
