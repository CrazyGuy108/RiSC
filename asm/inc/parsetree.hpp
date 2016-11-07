#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include <iterator>      // for forward_iterator_tag
#include "lexer.hpp"     // for Lexer
#include "parsenode.hpp" // for ParseNode

class ParseTree
{
public:
	class const_iterator
	{
	public:
		typedef ParseNode                 value_type;
		typedef std::ptrdiff_t            difference_type;
		typedef ParseNode*                pointer;
		typedef ParseNode&                reference;
		typedef std::forward_iterator_tag iterator_category;

		bool operator==(const const_iterator& a) const;
		bool operator!=(const const_iterator& a) const;

		const reference operator*() const;
		const pointer operator->() const;

		const_iterator& operator++();    // prefix
		const_iterator& operator++(int); // postfix

	private:
		const ParseNode* ptr;
	};

	class iterator
		: public const_iterator
	{
	public:
		reference operator*() const;
		pointer operator->() const;

		iterator& operator++();    // prefix
		iterator& operator++(int); // postfix

	private:
		ParseNode* ptr;
	};

	ParseTree() = default;
	ParseTree(const char* program); // lex and parse the given program
	ParseTree(Lexer& lexer);        // parse the program using the given lexer

	ParseTree(const ParseTree&) = delete;
	ParseTree& operator=(const ParseTree&) = delete;

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse the program using the given lexer

private:
	ParseNode* root; // root of the parse tree
	ParseNode* node; // iterator

	void advanceNode();
};

#endif // PARSETREE_HPP
