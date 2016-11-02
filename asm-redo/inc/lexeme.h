#ifndef LEXEME_H
#define LEXEME_H

#include <iosfwd> // for ostream forward declaration

// non-terminated substring of the source code
class Lexeme
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Lexeme& l);
	friend bool operator<(const Lexeme& l, const Lexeme& r);

	Lexeme() = default;
	Lexeme(const char* beg, const char* end);

	// for string literals
	template<size_t len>
	constexpr Lexeme(const char(&str)[len])
		: beg{ str }, end{ &str[len] } {}

	const char* getBeg() const; // gets beg
	const char* getEnd() const; // gets end

	void setBeg(const char* beg); // sets beg
	void setEnd(const char* end); // sets end

	size_t length() const; // gets length of substring

	int cmp(const Lexeme& l) const;

private:
	const char* beg; // beginning of lexeme
	const char* end; // end of lexeme
};

#endif // LEXEME_H
