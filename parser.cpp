

#include "parser.h"
#include "token.h"
#include "production.h"


namespace pratt {


Parser::Parser(std::istream& st)
		: lex(st) {
	tk = lex.Get();
}

// this is where expressions are being parsed into tokens
// explanation on how this works can be found in main.cpp
pratt::production::Production* Parser::Expression(int rbp) {
	pratt::token::Token* last = tk;
	tk = lex.Get();

	pratt::production::Production* left = last->Nud(this);

	while (tk && rbp < tk->Lbp() && lex.st.peek() != ';') {
		delete last;
		last = tk;
		tk = lex.Get();

		left = last->Led(this, left);
	}

	delete last;

	return left;
}

Parser::~Parser() {
	delete tk;
}

} // namespace pratt
