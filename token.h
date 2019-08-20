

#ifndef PRATT_TOKEN_H
#define PRATT_TOKEN_H


#include "parser.h"
#include "production.h"


namespace pratt {
namespace token {


class Token {

public:
	virtual pratt::production::Production* Nud(pratt::Parser*);
	virtual pratt::production::Production* Led(pratt::Parser*, pratt::production::Production*);
	virtual int Lbp();
};


class Integer : public Token {

public:
	int Value;

	Integer(int);

	virtual pratt::production::Production* Nud(pratt::Parser*);
};

template<class P, int lbp>
class PrefixOp : public Token {

public:
	virtual pratt::production::Production* Nud(pratt::Parser* p) {
		return new P(p->Expression(this->Lbp()));
	}

	virtual int Lbp() {
		return lbp;
	}
};

template<class P, int lbp>
class PostfixOp : public Token {

public:
	virtual pratt::production::Production* Led(pratt::Parser*, pratt::production::Production* lhs) {
		return new P(lhs);
	}

	virtual int Lbp() {
		return lbp;
	}
};

template<class P, int lbp> // Result production, Precedence
class InfixOp : public Token {

public:
	virtual pratt::production::Production* Led(pratt::Parser* p, pratt::production::Production* lhs) {
		return new P(lhs, p->Expression(this->Lbp()));
	}

	virtual int Lbp() {
		return lbp;
	}
};

typedef InfixOp<pratt::production::Assign, pratt::BP_Assignment> Assign;
//typedef InfixOp<pratt::production::OrAssign, pratt::BP_Assignment> OrAssign;
//typedef InfixOp<pratt::production::XorAssign, pratt::BP_Assignment> XorAssign;
//typedef InfixOp<pratt::production::AndAssign, pratt::BP_Assignment> AndAssign;
//typedef InfixOp<pratt::production::LshAssign, pratt::BP_Assignment> LshAssign;
//typedef InfixOp<pratt::production::LshAssign, pratt::BP_Assignment> RshAssign;
//typedef InfixOp<pratt::production::MulAssign, pratt::BP_Assignment> MulAssign;
//typedef InfixOp<pratt::production::DivAssign, pratt::BP_Assignment> DivAssign;
//typedef InfixOp<pratt::production::ModAssign, pratt::BP_Assignment> ModAssign;
//typedef InfixOp<pratt::production::AddAssign, pratt::BP_Assignment> AddAssign;
//typedef InfixOp<pratt::production::SubAssign, pratt::BP_Assignment> SubAssign;

typedef InfixOp<pratt::production::Or, pratt::BP_Or> Or;
typedef InfixOp<pratt::production::And, pratt::BP_And> And;
typedef PrefixOp<pratt::production::Not, pratt::BP_Unary> Not;

typedef InfixOp<pratt::production::BitOr, pratt::BP_BitOr> BitOr;
typedef InfixOp<pratt::production::BitXor, pratt::BP_BitXor> BitXor;
typedef InfixOp<pratt::production::BitAnd, pratt::BP_BitAnd> BitAnd;
typedef PrefixOp<pratt::production::BitNot, pratt::BP_Unary> BitNot;

typedef InfixOp<pratt::production::Equal, pratt::BP_Equality> Equal;
typedef InfixOp<pratt::production::NotEqual, pratt::BP_Equality> NotEqual;

typedef InfixOp<pratt::production::LessThan, pratt::BP_Relational> LessThan;
typedef InfixOp<pratt::production::GreaterThan, pratt::BP_Relational> GreaterThan;
typedef InfixOp<pratt::production::LessThanEqual, pratt::BP_Relational> LessThanEqual;
typedef InfixOp<pratt::production::GreaterThanEqual, pratt::BP_Relational> GreaterThanEqual;

typedef InfixOp<pratt::production::Lsh, pratt::BP_Shift> Lsh;
typedef InfixOp<pratt::production::Rsh, pratt::BP_Shift> Rsh;

typedef InfixOp<pratt::production::Mul, pratt::BP_Multiplicative> Mul;
typedef InfixOp<pratt::production::Div, pratt::BP_Multiplicative> Div;
typedef InfixOp<pratt::production::Mod, pratt::BP_Multiplicative> Mod;

class Add : public InfixOp<pratt::production::Add, pratt::BP_Additive> {

public:
	virtual pratt::production::Production* Nud(pratt::Parser*);
};

class Sub : public InfixOp<pratt::production::Sub, pratt::BP_Additive> {

public:
	virtual pratt::production::Production* Nud(pratt::Parser*);
};


}} // namespace pratt::token


#endif
