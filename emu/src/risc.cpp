#include "../inc/risc.hpp"

RiSC::RiSC()
	: ram{}, regs{}, pc{ 0 } {}

void RiSC::load(const char* bytecode, data_t length)
{
	for (size_t i{ 0 }; i < length; i += 2)
		mem(i) = bytecode[i - 1] << 8 | bytecode[i];
}

void RiSC::execute()
{
	inst_t inst;
	while (true)
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
			if (!i7(inst))
			{
				reg(ra(inst)) = pc + 1;
				pc = reg(rb(inst)) - 1; // counterracts the ++pc
			}
			else // syscall
			{
				switch (i7(inst))
				{
				case 1: // Halt - Stop machine and print state
					for (size_t i{ 1 }; i < regs_count; ++i)
						std::cout << "r" << i << ": " << reg(i) << '\n';

					std::cout << "pc: " << pc << std::endl;

				case 2: // Exit - Stop machine
					return;
				}
			}

			break;

		default:
			exit(1); // should never happen
		}

		++pc;
	}
}

data_t RiSC::getRam(data_t addr)
{
	return mem(addr);
}

data_t RiSC::getReg(data_t addr)
{
	return reg(addr);
}

data_t& RiSC::mem(data_t addr)
{
	if (addr < ram_length)
		return ram[addr];
	else
		exit(1); // should never happen
}

data_t& RiSC::reg(data_t addr)
{
	if (addr < regs_count)
	{
		if (!addr) // accessing zero register
			regs[0] = 0; // reading will always produce 0
		return regs[addr];
	}
	else
		exit(1); // should never happen
}
