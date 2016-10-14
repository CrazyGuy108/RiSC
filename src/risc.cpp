#include "../include/risc.h"

RiSC::RiSC()
	: ram{}, regs{}, pc{ 0 } {}

void RiSC::load(uword_t* program, uword_t length)
{
	for (uword_t i{ 0 }; i < length; ++i)
		mem(i) = program[i];
}

void RiSC::execute(uword_t start, uword_t end)
{
	pc = start;
	inst_t inst;
	while (pc < end)
	{
		inst = mem(pc);
		switch (op(inst))
		{
		case add:
			reg(ra(inst)) = reg(rb(inst)) + reg(rc(inst));
			break;

		case addi:
			reg(ra(inst)) = reg(rb(inst)) + i7(inst);
			break;

		case nand:
			reg(ra(inst)) = ~(reg(rb(inst)) & reg(rc(inst)));
			break;

		case lui:
			reg(ra(inst)) = i10(inst);
			break;

		case sw:
			mem(reg(rb(inst)) + i7(inst)) = reg(ra(inst));
			break;

		case lw:
			reg(ra(inst)) = mem(reg(rb(inst)) + i7(inst));
			break;

		case beq:
			if (reg(ra(inst)) == reg(rb(inst)))
				pc += i7(inst);
			break;

		case jalr:
			if (i7(inst))
				; // syscall
			else
			{
				reg(ra(inst)) = pc + 1;
				pc = reg(rb(inst)) - 1; // counterracts the ++pc
			}

			break;

		default:
			; // error: undefined opcode (should never happen)
		}

		++pc;
	}
}

uword_t RiSC::getRam(uword_t addr)
{
	return mem(addr);
}

uword_t RiSC::getReg(uword_t addr)
{
	return reg(addr);
}

uword_t& RiSC::mem(uword_t addr)
{
	if (addr < ram_length)
		return ram[addr];
	else
		; // error: mem index out of range
}

uword_t& RiSC::reg(uword_t addr)
{
	if (addr < regs_count)
	{
		if (!addr) // accessing zero register
			regs[0] = 0; // reading will always produce 0
		return regs[addr];
	}
	else
		; // error: reg index out of range
}
