#include "../inc/risc.hpp"

RiSC::RiSC()
	: pc{ 0 } {}

void RiSC::load(const char* bytecode, data_t length)
{
	for (size_t i{ 1 }, j{ 0 }; i < length; i += 2, ++j)
		ram[j] = (inst_t)(((inst_t)bytecode[i - 1] << 8) | (unsigned char)bytecode[i]);
}

void RiSC::start()
{
	while (true)
	{
		execute(ram[pc]);
		++pc;
	}
}

void RiSC::execute(inst_t inst)
{
	switch (op(inst))
	{
	case ADD:
		add(inst);
		break;
	case ADDI:
		addi(inst);
		break;
	case NAND:
		nand(inst);
		break;
	case LUI:
		lui(inst);
		break;
	case SW:
		sw(inst);
		break;
	case LW:
		lw(inst);
		break;
	case BEQ:
		beq(inst);
		break;
	case JALR:
		jalr(inst);
		break;
	default:
		throw std::out_of_range{ "invalid opcode" }; // should never happen
	}
}

void RiSC::add(inst_t inst)
{
	std::cout << "add r" << ra(inst) << " r" << rb(inst) << " r" << rc(inst) << '\n';
	reg(ra(inst)) = reg(rb(inst)) + reg(rc(inst));
}

void RiSC::addi(inst_t inst)
{
	std::cout << "addi r" << ra(inst) << " r" << rb(inst) << ' ' << i7(inst) << '\n';
	reg(ra(inst)) = reg(rb(inst)) + i7(inst);
}

void RiSC::nand(inst_t inst)
{
	std::cout << "nand r" << ra(inst) << " r" << rb(inst) << " r" << rc(inst) << '\n';
	reg(ra(inst)) = ~(reg(rb(inst)) & reg(rc(inst)));
}

void RiSC::lui(inst_t inst)
{
	std::cout << "lui r" << ra(inst) << ' ' << i10(inst) << '\n';
	reg(ra(inst)) = i10(inst);
}

void RiSC::sw(inst_t inst)
{
	std::cout << "sw r" << ra(inst) << " r" << rb(inst) << ' ' << i7(inst) << '\n';
	ram[reg(rb(inst)) + i7(inst)] = reg(ra(inst));
}

void RiSC::lw(inst_t inst)
{
	std::cout << "lw r" << ra(inst) << " r" << rb(inst) << ' ' << i7(inst) << '\n';
	reg(ra(inst)) = ram[reg(rb(inst)) + i7(inst)];
}

void RiSC::beq(inst_t inst)
{
	std::cout << "beq r" << ra(inst) << " r" << rb(inst) << ' ' << i7(inst) << '\n';
	if (reg(ra(inst)) == reg(rb(inst)))
		pc += i7(inst);
}

void RiSC::jalr(inst_t inst)
{
	std::cout << "jalr r" << ra(inst) << " r" << rb(inst) << ' ' << i7(inst) << '\n';
	if (!i7(inst))
	{
		reg(ra(inst)) = pc + 1;
		pc = reg(rb(inst)) - 1; // counterracts the ++pc
	}
	else
		syscall(inst);
}

void RiSC::syscall(inst_t inst)
{
	switch (i7(inst))
	{
	case 1: // Halt - Stop machine and print state
		for (size_t i{ 1 }; i < regs.size(); ++i)
			std::cout << "r" << i << ": " << reg(i) << '\n';

		std::cout << "pc: " << pc << std::endl;

	case 2: // Exit - Stop machine
		return;

	default:
		throw std::out_of_range{ "invalid syscall id" };
	}
}

RiSC::data_t& RiSC::reg(data_t addr)
{
	if (addr == 0)
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
