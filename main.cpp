/*
HOW IT WORKS:

1. User is prompted to input 1 or more expressions. To input more than 1 expression,
   separate expressions with a ';' (e.g., 1+1; 2+2). You may optionally add a ';' on
   the last expression.

   Example expressions:
   4+5*3
   4 * 5 + 3 * -12;
   1 && 0 || 1; true and false or true;		both expressions are the same

2. Parser calls lexer (Lexer::Get()) to identify all the tokens in the expression(s).
3. Parser then creates a parse tree in the form of Production class.
4. To evaluate the expression(s), Production::Evaluate() is called. This outputs a
   step by step evaluation of the expression(s). You may visualize Production::Evaluate()
   as doing the same thing when you are deriving a BNF grammar, hence the reason why the 
   class is named Production.

To further understand the terminologies used in this project, here is a sample BNF grammar:

Nonterminal/LHS					Terminal/RHS

<expr>       -> <expr> + <term> | <expr> - <term> | <term>
<term>       -> <term> * <factor> | <term> / <factor> | <factor>
<factor>     -> ( expr ) | <identifier> | <number>
<identifier> -> <letter> | <identifier><letter> | <identifier><digit>
<number>     -> <digit> | <number><digit>
<digit>      -> 0 | 1 | 2 | ... | 9
<letter>     -> a | b | c | ... | z

LHS (left-hand side) - are nonterminals
RHS (right-hand side) - a string of terminals and/or nonterminals
Nonterminal - enclosed in angle brackets (e.g., <expr>, <term>, etc.)
Terminal - a lexeme or token
Lexeme - lowest level syntactic unit of a language (e.g., +, -, *, /, 1, 2, 3, a, b, c, etc.)
Token - category of lexemes (e.g., keyword, identifier, operator, delimiter)

*/

#include <iostream>
#include <algorithm> // for std::count

#include "parser.h"
#include "production.h"


int main(int argc, char* argv[]) {
	std::cout << "Enter expression: ";

	std::string str;
	std::getline(std::cin, str);
	std::istringstream inp(str);

	pratt::Parser p = pratt::Parser(inp);

	// count the number of expressions, by counting the occurrences of ';'
	size_t n = std::count(str.begin(), str.end(), ';') + 1;

	// allocate memory for result with size n
	pratt::production::Production** result = (pratt::production::Production**)malloc(n * sizeof(pratt::production::Production*));

	// while lexer hasn't reached the end of the
	// input, keep on parsing  the expression(s)
	int e = 0;
	while (p.lex.st.peek() != EOF) {
		result[e++] = p.Expression(0);
	}
	result[e] = NULL; // mark the end of the result by assigning NULL (0)

	std::cout << "\nInput length: " << str.length() << std::endl;
	std::cout << "\nNumber of expressions: " << e << "\n\n";

	// if there are more than 0 expressions, evaluate them
	if (e > 0) {
		std::cout << "Evaluation:\n\n";
		// while result hasn't reached the end (NULL), keep on evaluating
		while (*result) {
			(*result++)->Evaluate();
			std::cout << std::endl;
		}
	}

	if (str.length() > 0)
		p.lex.PrintTokens();

	std::cin.get();

	return 0;
}
