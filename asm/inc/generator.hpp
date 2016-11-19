#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <utility>     // for pair
#include <vector>      // for vector
#include "parser.hpp"  // for Parser
#include "utility.hpp" // for inst_t

class Generator
{
public:
	typedef std::map<Lexeme, inst_t> symbol_table;
	typedef std::vector<inst_t>      bytecode_list;

	Generator() = default;
	Generator(Parser& parser);

	void generate(Parser& parser);
	inst_t next();
	bool empty() const;
	size_t getErrors() const;
	const symbol_table& getSymbolTable() const;

private:
	enum class Bitwise : inst_t;

	// helpers

	inst_t assemble(Line& currentLine, size_t line);       // uses symtable to generate a line of code
	inst_t resolve(const Identifier& id) const;            // resolves a single identifier
	static inst_t compile(Line& currentLine, size_t line); // compiles a line of code

	static inst_t rrr(Bitwise op, const Line& currentLine);
	static inst_t rri(Bitwise op, const Line& currentLine, size_t line = 0);
	static inst_t ri(Bitwise op, const Line& currentLine);

	bytecode_list bytecode;           // stream of bytecode
	bytecode_list::const_iterator it; // keeps track of position
	size_t errors;                    // amount of errors encountered
	symbol_table symtable;            // table for resolving labels
};

enum class Generator::Bitwise : inst_t
{
	RA_SHIFT = 10,
	RB_SHIFT = 7,
	RA_MASK  = 0x1C00,
	RB_MASK  = 0x0380,
	RC_MASK  = 0x0007,
	I7_MASK  = 0x007F,
	I10_MASK = 0x03FF,

	ADD  = 0x0000,
	ADDI = 0x2000,
	NAND = 0x4000,
	LUI  = 0x6000,
	SW   = 0x8000,
	LW   = 0xA000,
	BEQ  = 0xC000,
	JALR = 0xE000
};

#endif // GENERATOR_HPP
