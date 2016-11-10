#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include <iterator>      // for forward_iterator_tag
#include <stack>         // for stack
#include "lexer.hpp"     // for Lexer
#include "parsenode.hpp" // for ParseNode

class ParseTree
{
private:
	// base iterator class for const_iterator and iterator
	template<typename T>
	class base_iterator;

public:
	typedef base_iterator<ParseNode>       iterator;
	typedef base_iterator<const ParseNode> const_iterator;

	ParseTree() = default;
	ParseTree(const char* program); // lex and parse the given program
	ParseTree(Lexer& lexer);        // parse the program using the given lexer

	ParseTree(const ParseTree&) = delete;
	ParseTree& operator=(const ParseTree&) = delete;

	void parse(const char* program); // lex and parse the given program
	void parse(Lexer& lexer);        // parse the program using the given lexer

	iterator begin() const;
	iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

private:
	ParseNode* root; // root of the parse tree
	ParseNode* node; // iterator

	void advanceNode();
};

template<typename T>
class ParseTree::base_iterator
{
public:
	typedef T                         value_type;
	typedef std::ptrdiff_t            difference_type;
	typedef T*                        pointer;
	typedef T&                        reference;
	typedef std::forward_iterator_tag iterator_category;

	base_iterator() = default;
	base_iterator(pointer ptr);

	bool operator==(const base_iterator& rhs) const;
	bool operator!=(const base_iterator& rhs) const;

	reference operator*() const;
	pointer operator->() const;

	base_iterator operator++();    // prefix
	base_iterator operator++(int); // postfix

private:
	pointer ptr;                // pointer to the current node
	std::stack<size_t> indexes; // sibling indexes that tell how the iterator got there
};

#endif // PARSETREE_HPP
