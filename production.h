
#ifndef PRATT_PRODUCTION_H
#define PRATT_PRODUCTION_H
#include <iostream>

namespace pratt {
namespace production {


class Production {

public:
	virtual int Evaluate() = 0;
};

class Terminal : public Production {

public:
	int Value;

	Terminal(int);

	virtual int Evaluate();
};

class PrefixOp : public Production {

public:
	Production* Right;

	PrefixOp(Production*);

	~PrefixOp() {
		delete Right;
	}
};

class PostfixOp : public Production {

public:
	Production* Left;

	PostfixOp(Production*);

	~PostfixOp() {
		delete Left;
	}
};

class InfixOp : public Production {

public:
	Production* Left;
	Production* Right;

	InfixOp(Production*, Production*);

	~InfixOp() {
		delete Left;
		delete Right;
	}
};

class Assign : public InfixOp {

public:
	Assign(Production*, Production*);

	virtual int Evaluate();
};

class Or : public InfixOp {

public:
	Or(Production*, Production*);

	virtual int Evaluate();
};

class And : public InfixOp {

public:
	And(Production*, Production*);

	virtual int Evaluate();
};

class Not : public PrefixOp {

public:
	Not(Production*);

	virtual int Evaluate();
};

class BitOr : public InfixOp {

public:
	BitOr(Production*, Production*);

	virtual int Evaluate();
};

class BitXor : public InfixOp {

public:
	BitXor(Production*, Production*);

	virtual int Evaluate();
};

class BitAnd : public InfixOp {

public:
	BitAnd(Production*, Production*);

	virtual int Evaluate();
};

class BitNot : public PrefixOp {

public:
	BitNot(Production*);

	virtual int Evaluate();
};

class Equal : public InfixOp {

public:
	Equal(Production*, Production*);

	virtual int Evaluate();
};

class NotEqual : public InfixOp {

public:
	NotEqual(Production*, Production*);

	virtual int Evaluate();
};

class LessThan : public InfixOp {

public:
	LessThan(Production*, Production*);

	virtual int Evaluate();
};

class GreaterThan : public InfixOp {

public:
	GreaterThan(Production*, Production*);

	virtual int Evaluate();
};

class LessThanEqual : public InfixOp {

public:
	LessThanEqual(Production*, Production*);

	virtual int Evaluate();
};

class GreaterThanEqual : public InfixOp {

public:
	GreaterThanEqual(Production*, Production*);

	virtual int Evaluate();
};

class Lsh : public InfixOp {

public:
	Lsh(Production*, Production*);

	virtual int Evaluate();
};

class Rsh : public InfixOp {

public:
	Rsh(Production*, Production*);

	virtual int Evaluate();
};

class Mul : public InfixOp {

public:
	Mul(Production*, Production*);

	virtual int Evaluate();
};

class Div : public InfixOp {

public:
	Div(Production*, Production*);

	virtual int Evaluate();
};

class Mod : public InfixOp {

public:
	Mod(Production*, Production*);

	virtual int Evaluate();
};

class Add : public InfixOp {

public:
	Add(Production*, Production*);

	virtual int Evaluate();
};

class Sub : public InfixOp {

public:
	Sub(Production*, Production*);

	virtual int Evaluate();
};


}} // namespace pratt::production


#endif
