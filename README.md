# Math-Pratt
A COSC65 math parser project based on the Pratt Parser.

## How it works
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

```
Nonterminal/LHS			Terminal/RHS
<expr>       -> <expr> + <term> | <expr> - <term> | <term>
<term>       -> <term> * <factor> | <term> / <factor> | <factor>
<factor>     -> ( expr ) | <identifier> | <number>
<identifier> -> <letter> | <identifier><letter> | <identifier><digit>
<number>     -> <digit> | <number><digit>
<digit>      -> 0 | 1 | 2 | ... | 9
<letter>     -> a | b | c | ... | z
```

LHS (left-hand side) - are nonterminals\
RHS (right-hand side) - a string of terminals and/or nonterminals\
Nonterminal - enclosed in angle brackets (e.g., \<expr\>, \<term\>, etc.)\
Terminal - a lexeme or token\
Lexeme - lowest level syntactic unit of a language (e.g., +, -, *, /, 1, 2, 3, a, b, c, etc.)\
Token - category of lexemes (e.g., keyword, identifier, operator, delimiter)
