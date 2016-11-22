#ifndef RISC_HPP
#define RISC_HPP

#include <array>     // for array
#include <cstdint>   // for uint16_t
#include <iostream>  // for cout
#include <stdexcept> // for out_of_range

class RiSC
{
public:
	typedef uint16_t inst_t; // instruction word
	typedef uint16_t data_t; // data word

	// represents a single block of memory
	template<size_t len>
	using Memory = std::array<data_t, len>;

	RiSC();

	void load(const char* program, data_t length); // load a program into memory
	void start(); // start executing the program where the PC left off

private:
	enum Bitwise
		: inst_t;

	void execute(inst_t inst);

	void add(inst_t inst);
	void addi(inst_t inst);
	void nand(inst_t inst);
	void lui(inst_t inst);
	void sw(inst_t inst);
	void lw(inst_t inst);
	void beq(inst_t inst);
	void jalr(inst_t inst);

	void syscall(inst_t inst);

	data_t& reg(data_t addr);
	data_t  reg(data_t addr) const;

	static inst_t op(inst_t inst);
	static inst_t ra(inst_t inst);
	static inst_t rb(inst_t inst);
	static inst_t rc(inst_t inst);
	static inst_t i7(inst_t inst);
	static inst_t i10(inst_t inst);

	Memory<65536> ram;
	Memory<8>     regs;
	data_t        pc;
};

enum RiSC::Bitwise
	: RiSC::inst_t
{
	ADD  = 0x0000,
	ADDI = 0x2000,
	NAND = 0x4000,
	LUI  = 0x6000,
	SW   = 0x8000,
	LW   = 0xA000,
	BEQ  = 0xC000,
	JALR = 0xE000,

	OP_MASK  = 0xE000,
	RA_MASK  = 0x1C00,
	RB_MASK  = 0x0380,
	RC_MASK  = 0x0007,
	I7_MASK  = 0x003F,
	I7_SIGN  = 0x0020,
	I10_MASK = 0x03FF,

	RA_SHIFT  = 10,
	RB_SHIFT  = 7,
	I10_SHIFT = 6
};

#endif // RISC_HPP
