#include "../inc/generator.hpp"

Generator::Generator(Parser& parser)
	: errors{ 0 }
{
	generate(parser);
}

void Generator::generate(Parser& parser)
{
	std::vector<std::pair<Line*, inst_t>> failed; // holds lines that failed to compile given the current context
	Line* currentLine;
	size_t line{ 0 };

	while (!parser.empty())
	{
		currentLine = parser.next();

		// add label to symbol table if existent
		if(dynamic_cast<LineWithLabel*>(currentLine) != nullptr)
			symtable.emplace(dynamic_cast<LineWithLabel*>(currentLine)->getLabel(), line);

		try
		{
			// attempt to compile
			assemble(*currentLine);
		}
		catch (const std::invalid_argument& e)
		{
			failed.emplace_back(currentLine, line); // save for later
			bytecode.emplace_back(0); // leave a nop as a placeholder
		}

		++line;
	}

	for (const auto& i : failed)
	{
		try
		{
			// attempt to compile again given the complete symtable
			assemble(*i.first);
		}
		catch (const std::invalid_argument& e)
		{
			// error: undefined identifier
			++errors;
		}
	}

	it = bytecode.cbegin();
}

inst_t Generator::next()
{
	return *it++;
}

bool Generator::empty() const
{
	return it == bytecode.cend();
}

size_t Generator::getErrors() const
{
	return errors;
}

const Generator::symbol_table& Generator::getSymbolTable() const
{
	return symtable;
}

void Generator::assemble(const Line& line)
{
	Line noID{ line.getOpcode() };

	// fill in identifiers using the symbol table
	for (auto& i : line.getOperands())
		noID.addOperand(dynamic_cast<Identifier*>(i) != nullptr ?
			new Immediate{ resolve(*dynamic_cast<Identifier*>(i)) } : i);

	bytecode.push_back(compile(noID));
}

inst_t Generator::resolve(const Identifier& id) const
{
	const Lexeme& lexeme{ id.getID() };
	symbol_table::const_iterator it{ symtable.find(lexeme) };
	if (it != symtable.cend()) // label definition matches the identifier
		return it->second;
	else
		throw std::invalid_argument{ std::string{ lexeme.getBeg(), lexeme.length() } };
}

inst_t Generator::compile(const Line& line)
{
	switch (line.getOpcode())
	{
	case Token::ADD:
		return rrr(Bitwise::ADD, line);
		break;
	case Token::ADDI:
		return rri(Bitwise::ADDI, line);
		break;
	case Token::NAND:
		return rrr(Bitwise::NAND, line);
		break;
	case Token::LUI:
		return ri(Bitwise::LUI, line);
		break;
	case Token::SW:
		return rri(Bitwise::SW, line);
		break;
	case Token::LW:
		return rri(Bitwise::LW, line);
		break;
	case Token::BEQ:
		return rri(Bitwise::BEQ, line);
		break;
	case Token::JALR:
		return rri(Bitwise::JALR, line);
		break;
	default:
		; // error: invalid opcode
	}
}

inst_t Generator::rrr(Bitwise op, const Line& line)
{
	if (line.getOperands().size() == 3)
	{
		Register* ra{ dynamic_cast<Register*>(line.getOperands()[0]) };
		Register* rb{ dynamic_cast<Register*>(line.getOperands()[1]) };
		Register* rc{ dynamic_cast<Register*>(line.getOperands()[2]) };
		if (ra != nullptr)
			if(rb != nullptr)
				if (rc != nullptr)
					return (inst_t)op | (ra->getReg() << (inst_t)Bitwise::RA_SHIFT) | (rb->getReg() << (inst_t)Bitwise::RB_SHIFT) | rc->getReg();
				else
					throw std::invalid_argument{ "expected register for operand 3" };
			else
				throw std::invalid_argument{ "expected register for operand 2" };
		else
			throw std::invalid_argument{ "expected register for operand 1" };
	}
	else
		throw std::invalid_argument{ "operand amount is not 3" };
}

inst_t Generator::rri(Bitwise op, const Line& line)
{
	if (line.getOperands().size() == 3)
	{
		Register* ra{ dynamic_cast<Register*>(line.getOperands()[0]) };
		Register* rb{ dynamic_cast<Register*>(line.getOperands()[1]) };
		Immediate* i7{ dynamic_cast<Immediate*>(line.getOperands()[2]) };
		if (ra != nullptr)
			if (rb != nullptr)
				if (i7 != nullptr)
					return (inst_t)op | (ra->getReg() << (inst_t)Bitwise::RA_SHIFT) | (rb->getReg() << (inst_t)Bitwise::RB_SHIFT) | (i7->getImm() & (inst_t)Bitwise::I7_MASK);
				else
					throw std::invalid_argument{ "expected immediate for operand 3" };
			else
				throw std::invalid_argument{ "expected register for operand 2" };
		else
			throw std::invalid_argument{ "expected register for operand 1" };
	}
	else
		throw std::invalid_argument{ "operand amount is not 3" };
}

inst_t Generator::ri(Bitwise op, const Line& line)
{
	if (line.getOperands().size() == 2)
	{
		Register* ra{ dynamic_cast<Register*>(line.getOperands()[0]) };
		Immediate* i10{ dynamic_cast<Immediate*>(line.getOperands()[1]) };
		if (ra != nullptr)
			if (i10 != nullptr)
				return (inst_t)op | (ra->getReg() << (inst_t)Bitwise::RA_SHIFT) | (i10->getImm() & (inst_t)Bitwise::I10_MASK);
			else
				throw std::invalid_argument{ "expected immediate for operand 2" };
		else
			throw std::invalid_argument{ "expected register for operand 1" };
	}
	else
		throw std::invalid_argument{ "operand amount is not 2" };
}
