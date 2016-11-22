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
		if (dynamic_cast<LineWithLabel*>(currentLine) != nullptr)
			symtable.emplace(dynamic_cast<LineWithLabel*>(currentLine)->getLabel(), line);

		try
		{
			// attempt to compile
			bytecode.emplace_back(assemble(*currentLine, line));
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
			bytecode[i.second] = assemble(*i.first, i.second);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "generator error(" << line << "): " << e.what() << '\n';
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

inst_t Generator::assemble(Line& currentLine, size_t line)
{
	// fill in identifiers using the symbol table
	for (auto& i : currentLine.getOperands())
		if (dynamic_cast<Identifier*>(i) != nullptr)
		{
			Immediate* tmp{ new Immediate{ resolve(*dynamic_cast<Identifier*>(i)) } };
			delete i;
			i = tmp;
		}

	return compile(currentLine, line);
}

inst_t Generator::resolve(const Identifier& id) const
{
	const Lexeme& lexeme{ id.getID() };
	symbol_table::const_iterator it{ symtable.find(lexeme) };
	if (it != symtable.cend()) // label definition matches the identifier
		return it->second;
	else
		throw std::invalid_argument{ "unresolved identifier \"" + std::string{ lexeme.getBeg(), lexeme.length() } + '\"' };
}

inst_t Generator::compile(Line& currentLine, size_t line)
{
	switch (currentLine.getOpcode())
	{
	case Token::ADD:
		return rrr(Bitwise::ADD, currentLine);
	case Token::ADDI:
		return rri(Bitwise::ADDI, currentLine);
	case Token::NAND:
		return rrr(Bitwise::NAND, currentLine);
	case Token::LUI:
		return ri(Bitwise::LUI, currentLine);
	case Token::SW:
		return rri(Bitwise::SW, currentLine);
	case Token::LW:
		return rri(Bitwise::LW, currentLine);
	case Token::BEQ:
		return rri(Bitwise::BEQ, currentLine, line + 1);
	case Token::JALR:
		return rri(Bitwise::JALR, currentLine);
	default:
		throw std::invalid_argument{ "invalid opcode" }; // should never happen
	}
}

inst_t Generator::rrr(Bitwise op, const Line& currentLine)
{
	if (currentLine.getOperands().size() == 3)
	{
		Register* ra{ dynamic_cast<Register*>(currentLine.getOperands()[0]) };
		Register* rb{ dynamic_cast<Register*>(currentLine.getOperands()[1]) };
		Register* rc{ dynamic_cast<Register*>(currentLine.getOperands()[2]) };
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

inst_t Generator::rri(Bitwise op, const Line& currentLine, size_t line)
{
	if (currentLine.getOperands().size() == 3)
	{
		Register* ra{ dynamic_cast<Register*>(currentLine.getOperands()[0]) };
		Register* rb{ dynamic_cast<Register*>(currentLine.getOperands()[1]) };
		Immediate* i7{ dynamic_cast<Immediate*>(currentLine.getOperands()[2]) };
		if (ra != nullptr)
			if (rb != nullptr)
				if (i7 != nullptr)
					return (inst_t)op | (ra->getReg() << (inst_t)Bitwise::RA_SHIFT) | (rb->getReg() << (inst_t)Bitwise::RB_SHIFT) | ((i7->getImm() - line) & (inst_t)Bitwise::I7_MASK);
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

inst_t Generator::ri(Bitwise op, const Line& currentLine)
{
	if (currentLine.getOperands().size() == 2)
	{
		Register* ra{ dynamic_cast<Register*>(currentLine.getOperands()[0]) };
		Immediate* i10{ dynamic_cast<Immediate*>(currentLine.getOperands()[1]) };
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
