
#include "production.h"


namespace pratt {
namespace production {


// class Production


// class Terminal

Terminal::Terminal(int v)
		: Value(v) {
}

int Terminal::Evaluate() {
	return Value;
}


// class InfixOp

InfixOp::InfixOp(Production* lhs, Production* rhs) 
		: Left(lhs), Right (rhs) {
}


// class PrefixOp

PrefixOp::PrefixOp(Production* rhs)
	: Right(rhs) {
}


// class PostfixOp

PostfixOp::PostfixOp(Production* lhs)
	: Left(lhs) {
}


// class Assign

Assign::Assign(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Assign::Evaluate() {
	int ret = Right->Evaluate();
	std::cout << " = " << ret << std::endl;
	return ret;
}


// class Or

Or::Or(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Or::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l || r;
	std::cout << l << " || " << r << " = " << ret << std::endl;
	return ret;
}


// class And

And::And(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int And::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l && r;
	std::cout << l << " && " << r << " = " << ret << std::endl;
	return ret;
}


// class Not

Not::Not(Production* rhs)
	: PrefixOp(rhs) {
}

int Not::Evaluate() {
	int r = Right->Evaluate();
	int ret = !r;
	std::cout << "!" << r << " = " << ret << std::endl;
	return ret;
}


// class BitOr

BitOr::BitOr(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int BitOr::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l | r;
	std::cout << l << " | " << r << " = " << ret << std::endl;
	return ret;
}


// class BitXor

BitXor::BitXor(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int BitXor::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l ^ r;
	std::cout << l << " ^ " << r << " = " << ret << std::endl;
	return ret;
}


// class BitAnd

BitAnd::BitAnd(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int BitAnd::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l & r;
	std::cout << l << " & " << r << " = " << ret << std::endl;
	return ret;
}


// class BitNot

BitNot::BitNot(Production* rhs)
	: PrefixOp(rhs) {
}

int BitNot::Evaluate() {
	int r = Right->Evaluate();
	int ret = ~r;
	std::cout << "~" << r << " = " << ret << std::endl;
	return ret;
}


// class Equal

Equal::Equal(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Equal::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l == r;
	std::cout << l << " == " << r << " = " << ret << std::endl;
	return ret;
}


// class NotEqual

NotEqual::NotEqual(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int NotEqual::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l != r;
	std::cout << l << " != " << r << " = " << ret << std::endl;
	return ret;
}


// class LessThan

LessThan::LessThan(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int LessThan::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l < r;
	std::cout << l << " < " << r << " = " << ret << std::endl;
	return ret;
}


// class GreaterThan

GreaterThan::GreaterThan(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int GreaterThan::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l > r;
	std::cout << l << " > " << r << " = " << ret << std::endl;
	return ret;
}


// class LessThanEqual

LessThanEqual::LessThanEqual(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int LessThanEqual::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l <= r;
	std::cout << l << " <= " << r << " = " << ret << std::endl;
	return ret;
}


// class GreaterThanEqual

GreaterThanEqual::GreaterThanEqual(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int GreaterThanEqual::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l >= r;
	std::cout << l << " >= " << r << " = " << ret << std::endl;
	return ret;
}


// class Lsh

Lsh::Lsh(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Lsh::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l << r;
	std::cout << l << " << " << r << " = " << ret << std::endl;
	return ret;
}


// class Rsh

Rsh::Rsh(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Rsh::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l >> r;
	std::cout << l << " >> " << r << " = " << ret << std::endl;
	return ret;
}


// class Mul

Mul::Mul(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Mul::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l * r;
	std::cout << l << " * " << r << " = " << ret << std::endl;
	return ret;
}


// class Div

Div::Div(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Div::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l / r;
	std::cout << l << " / " << r << " = " << ret << std::endl;
	return ret;
}


// class Mod

Mod::Mod(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Mod::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l % r;
	std::cout << l << " % " << r << " = " << ret << std::endl;
	return ret;
}


// class Add

Add::Add(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Add::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l + r;
	std::cout << l << " + " << r << " = " << ret << std::endl;
	return ret;
}


// class Sub

Sub::Sub(Production* lhs, Production* rhs)
	: InfixOp(lhs, rhs) {
}

int Sub::Evaluate() {
	int l = Left->Evaluate();
	int r = Right->Evaluate();
	int ret = l - r;
	std::cout << l << " - " << r << " = " << ret << std::endl;
	return ret;
}


}} // namespace pratt::production