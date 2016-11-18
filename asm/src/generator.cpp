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
		break;
	case Token::ADDI:
		break;
	case Token::NAND:
		break;
	case Token::LUI:
		break;
	case Token::SW:
		break;
	case Token::LW:
		break;
	case Token::BEQ:
		break;
	case Token::JALR:
		break;
	default:
		; // error: invalid opcode
	}
}
