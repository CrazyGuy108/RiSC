#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>      // for vector
#include "lexeme.hpp"  // for Lexeme
#include "lexer.hpp"   // for Lexer
#include "utility.hpp" // for Keyword

// forward declare base classes

class Line;
class Operand;

// verifies and organizes a stream of tokens from the Lexer
class Parser final
{
public:
	Parser() = default;
	Parser(Lexer& lexer);
	~Parser();

	void parse(Lexer& lexer); // parse using the given lexer

	Line* next();       // get the next Line
	bool empty() const; // checks if the lines container is empty

private:
	std::vector<Line*> lines; // stream of Lines created by the parser
	std::vector<Line*>::const_iterator it; // current position of stream
};

// represents a parsed and tokenized line of code
class Line
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Line& line);

	Line() = default;
	Line(Token::Type opcode);
	virtual ~Line();

	Token::Type getOpcode() const;
	Operand* getOperand(size_t index);
	const Operand* getOperand(size_t index) const;

	void setOpcode(Token::Type opcode);
	void addOperand(Operand* operand);

protected:
	Token::Type opcode;
	std::vector<Operand*> operands;
};

// similar to a Line but with a label
class LineWithLabel final
	: public Line
{
public:
	LineWithLabel(const Lexeme& label);
	virtual ~LineWithLabel() override final = default;

	const Lexeme& getLabel() const;

private:
	Lexeme label;
};

// abstract base class for operands
class Operand
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Operand& operand);

	Operand() = default;
	virtual ~Operand() = 0;
};

// register operand
class Register final
	: public Operand
{
public:
	Register(inst_t reg);
	Register(const Lexeme& lexeme);
	virtual ~Register() override final = default;

	inst_t getReg() const;

private:
	inst_t reg;
};

// immediate operand
class Immediate final
	: public Operand
{
public:
	Immediate(inst_t imm);
	Immediate(const Lexeme& lexeme);
	virtual ~Immediate() override final = default;

	inst_t getImm() const;

private:
	inst_t imm;
};

// identifier operand
class Identifier final
	: public Operand
{
public:
	Identifier(const Lexeme& id);
	virtual ~Identifier() override final = default;

	const Lexeme& getID() const;

private:
	Lexeme id;
};

#endif // PARSER_HPP
