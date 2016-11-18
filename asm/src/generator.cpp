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
			compile(currentLine);
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
			compile(i.first);
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

void Generator::compile(Line* line)
{
	Line noID{ line->getOpcode() };
	Operand* operand;

	// fill in identifiers using the symbol table
	for (auto& i : line->getOperands())
	{
		operand = i;
		if (dynamic_cast<Identifier*>(i) != nullptr)
		{
			const Lexeme& lexeme{ dynamic_cast<Identifier*>(i)->getID() };
			symbol_table::iterator it{ symtable.find(lexeme) };
			if (it != symtable.end()) // found the name in the symbol table
				operand = new Immediate{ it->second };
			else
				throw std::invalid_argument{ std::string{ lexeme.getBeg(), lexeme.length() } };
		}

		noID.addOperand(operand);
	}

	// compile
	// (placeholder)
}
