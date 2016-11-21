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
		case ADD:
			reg(ra(inst)) = reg(rb(inst)) + reg(rc(inst));
			break;

		case ADDI:
			reg(ra(inst)) = reg(rb(inst)) + i7(inst);
			break;

		case NAND:
			reg(ra(inst)) = ~(reg(rb(inst)) & reg(rc(inst)));
			break;

		case LUI:
			reg(ra(inst)) = i10(inst);
			break;

		case SW:
			ram[reg(rb(inst)) + i7(inst)] = reg(ra(inst));
			break;

		case LW:
			reg(ra(inst)) = ram[reg(rb(inst)) + i7(inst)];
			break;

		case BEQ:
			if (reg(ra(inst)) == reg(rb(inst)))
				pc += i7(inst);
			break;

		case JALR:
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

RiSC::data_t& RiSC::reg(data_t addr)
{
	if(addr == 0)
		regs[addr] = 0;
	return regs[addr];
}

RiSC::data_t RiSC::reg(data_t addr) const
{
	if (addr == 0)
		return 0;
	else
		return regs[addr];
}

RiSC::inst_t RiSC::op(inst_t inst)
{
	return inst & OP_MASK;
}

RiSC::inst_t RiSC::ra(inst_t inst)
{
	return (inst & RA_MASK) >> RA_SHIFT;
}

RiSC::inst_t RiSC::rb(inst_t inst)
{
	return (inst & RB_MASK) >> RB_SHIFT;
}

RiSC::inst_t RiSC::rc(inst_t inst)
{
	return inst & RC_MASK;
}

RiSC::inst_t RiSC::i7(inst_t inst)
{
	return inst & I7_MASK | (inst & I7_SIGN ? ~I7_MASK : 0);
}

RiSC::inst_t RiSC::i10(inst_t inst)
{
	return (inst & I10_MASK) << I10_SHIFT;
}

