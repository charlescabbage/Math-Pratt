/*
TOKENS:

+---------------------------+
| KEYWORD	     EQUIVALENT	|
+---------------------------+
| false				0		|
| true				1		|
| or				||		|
| or_eq				|=		|
| xor				^		|
| xor_eq			^=		|
| and				&&		|
| and_eq			&=		|
| not				!		|
| not_eq			!=		|
| bitor				|		|
| bitand			&		|
| compl				~		|
+---------------------------+

+---------------------------+
| DELIMITER	     EQUIVALENT	|
+---------------------------+
| semicolon			;		|
| whitespace		" "		|
| tab				\t		|
| EOL				\n		|
| carriage return	\r		|
+---------------------------+

+----------------------------------------------+
| CATEGORY		OPERATOR		ASSOCIATIVITY  |
+----------------------------------------------+
| Unary				+ - ! ~		Right to left  |
| Multiplicative	* / %		Left to right  |
| Additive			+ -			Left to right  |
| Shift				<< >>		Left to right  |
| Relational		< <= > >=	Left to right  |
| Equality			== !=		Left to right  |
| Bitwise AND		&			Left to right  |
| Bitwise XOR		^			Left to right  |
| Bitwise OR		|			Left to right  |
| Logical AND		&&			Left to right  |
| Logical OR		||			Left to right  |
+----------------------------------------------+
*/
#ifndef PRATT_LEXER_H
#define PRATT_LEXER_H


#include <sstream>
#include <map>

// #include "token.h"
namespace pratt { namespace token {
	class Token;
}}


namespace pratt {


class Lexer {

public:
	std::istream& st;

	// tokens - this is where all lexemes are stored
	std::map<int, std::string> key; // keyword
	std::map<int, std::string> ide; // identifier
	std::map<int, std::string> lit; // literal
	std::map<int, std::string> opt; // operator
	std::map<int, std::string> del; // delimiter

	Lexer(std::istream&);
	pratt::token::Token* Lookup(std::string);
	pratt::token::Token* Get();
	void PrintTokens();
};


} // namespace pratt


#endif