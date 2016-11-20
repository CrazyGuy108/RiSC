#include "../inc/risc.hpp"

RiSC::RiSC()
	: ram{}, regs{}, pc{ 0 } {}

void RiSC::load(const char* bytecode, data_t length)
{
	for (size_t i{ 0 }; i < length; i += 2)
		ram[i] = bytecode[i - 1] << 8 | bytecode[i];
}

void RiSC::execute()
{
	inst_t inst;
	while (true)
	{
		inst = ram[pc];
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
			ram[reg(rb(inst)) + i7(inst)] = reg(ra(inst));
			break;

		case lw:
			reg(ra(inst)) = ram[reg(rb(inst)) + i7(inst)];
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
					for (size_t i{ 1 }; i < regs.size(); ++i)
						std::cout << "r" << i << ": " << reg(i) << '\n';

					std::cout << "pc: " << pc << std::endl;

				case 2: // Exit - Stop machine
					return;
				}
			}

			break;

		default:
			throw std::out_of_range{ "invalid syscall id" };
		}

		++pc;
	}
}

data_t& RiSC::reg(data_t addr)
{
	if(addr == 0)
		regs[addr] = 0;
	return regs[addr];
}

data_t RiSC::reg(data_t addr) const
{
	if (addr == 0)
		return 0;
	else
		return regs[addr];
}
