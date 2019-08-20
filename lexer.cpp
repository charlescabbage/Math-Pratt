

#include "token.h"
#include "lexer.h"


namespace pratt {


Lexer::Lexer(std::istream& s)
	: st(s) {
}

// used for looking up keywords or reserved words
pratt::token::Token* Lexer::Lookup(std::string s) {
	if (s == "false") {
		key[key.size()] = s;
		return new pratt::token::Integer(0);
	}
	else if (s == "true") {
		key[key.size()] = s;
		return new pratt::token::Integer(1);
	}
	else if (s == "or") {
		key[key.size()] = s;
		return new pratt::token::Or;
	}
	else if (s == "or_eq") {
		key[key.size()] = s;
		//return new pratt::token::OrAssign;
		return new pratt::token::Assign;
	}
	else if (s == "xor") {
		key[key.size()] = s;
		return new pratt::token::BitXor;
	}
	else if (s == "xor_eq") {
		key[key.size()] = s;
		//return new pratt::token::XorAssign;
		return new pratt::token::Assign;
	}
	else if (s == "and") {
		key[key.size()] = s;
		return new pratt::token::And;
	}
	else if (s == "and_eq") {
		key[key.size()] = s;
		//return new pratt::token::AndAssign;
		return new pratt::token::Assign;
	}
	else if (s == "not") {
		key[key.size()] = s;
		return new pratt::token::Not;
	}
	else if (s == "not_eq") {
		key[key.size()] = s;
		return new pratt::token::NotEqual;
	}
	else if (s == "bitor") {
		key[key.size()] = s;
		return new pratt::token::BitOr;
	}
	else if (s == "bitand") {
		key[key.size()] = s;
		return new pratt::token::BitAnd;
	}
	else if (s == "compl") {
		key[key.size()] = s;
		return new pratt::token::BitNot;
	}

	ide[ide.size()] = s; // if s is not a keyword, then it must be an identifier
	return new pratt::token::Integer(0);
}

// this is where all tokens are identified in the expression
pratt::token::Token* Lexer::Get() {
	char c = st.peek();

	if (!st)
		return NULL;

	//==================== START OF IDENTIFIERS ==================
	// variables or identifiers should start with a letter, '$', or '_' but should never start with a number
	else if (isalpha(c) || c == '$' || c == '_') {
		std::string value(1, c);
		while (true) {
			st.get();
			c = st.peek();
			// if we have confirmed that the variable started with a letter, '$', or '_'
			// allow numbers to be followed by it (e.g., abc123, _123, $123, _$123, etc.)
			if (isalpha(c) || isdigit(c) || c == '$' || c == '_') {
				value += c;
				continue;
			}
			return Lookup(value); // check if reserved word
		}
	}
	//====================== END OF VARIABLES ====================

	//===================== START OF LITERALS ====================
	else if (isdigit(c)) {
		int ret;
		//bool isfloat = false;
		//bool isdouble = false;
		std::stringstream ss;
		std::string value(1, c);
		if (c == '0') {
			st.get();
			c = st.peek();
			if (c == 'x' || c == 'X') { // hexadecimal (e.g., 0xDEADBEEF)
				value += c;
				while (true) {
					st.get();
					c = st.peek();
					if (isxdigit(c)) {
						value += c;
						continue;
					}
					ss << std::hex << value;
					ss >> ret;
					lit[lit.size()] = value;
					return new pratt::token::Integer(ret);
				}
			}
			else {
				goto nonhex;
			}
		}
		// decimal numbers are identified here
		// you can also implement it to work for float and double tokens
		while (true) {
			st.get();
			c = st.peek();
nonhex:
			if (isdigit(c) /*|| !isfloat && (!isdouble && c == '.' || c == 'f' || c == 'F')*/) {
				//if (c == '.') isdouble = true;
				//if (c == 'f' || c == 'F') isfloat = true;
				value += c;
				continue;
			}
			ss << value;
			ss >> ret;
			lit[lit.size()] = value;
			/*
			if (isfloat)
				return new pratt::token::Float(value);
			if (isdouble)
				return new pratt::token::Double(value);

			return new pratt::token::Integer(value);
			*/
			return new pratt::token::Integer(ret);
		}
	}
	//====================== END OF LITERALS =====================

	//==================== START OF OPERATORS ====================
	else if (c == '*') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // *=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::MulAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::Mul;
	}
	else if (c == '/') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // /=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::DivAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::Div;
	}
	else if (c == '%') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // %=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::ModAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::Mod;
	}
	else if (c == '+') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // +=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::AddAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::Add;
	}
	else if (c == '-') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // -=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::SubAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::Sub;
	}
	else if (c == '|') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '|') { // ||
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::Or;
		}
		else if (c == '=') { // |=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::OrAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::BitOr;
	}
	else if (c == '&') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '&') { // &&
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::And;
		}
		else if (c == '=') { // &=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::AndAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::BitAnd;
	}
	else if (c == '!') {
		opt[opt.size()] = c;;
		st.get();
		c = st.peek();
		if (c == '=') { // !=
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::NotEqual;
		}
		return new pratt::token::Not;
	}
	else if (c == '^') {
		opt[opt.size()] = c;;
		st.get();
		c = st.peek();
		if (c == '=') { // ^=
			opt[opt.size() - 1] += c;
			st.get();
			//return new pratt::token::XorAssign;
			return new pratt::token::Assign;
		}
		return new pratt::token::BitXor;
	}
	else if (c == '~') {
		opt[opt.size()] = c;
		st.get();
		return new pratt::token::BitNot;
	}
	else if (c == '<') {
		opt[opt.size()] = c;;
		st.get();
		c = st.peek();
		if (c == '<') { // <<
			opt[opt.size() - 1] += c;
			st.get();
			c = st.peek();
			if (c == '=') { // <<=
				opt[opt.size() - 1] += c;;
				st.get();
				//return new pratt::token::LshAssign;
				return new pratt::token::Assign;
			}
			return new pratt::token::Lsh;
		}
		else if (c == '=') { // <=
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::LessThanEqual;
		}
		return new pratt::token::LessThan;
	}
	else if (c == '>') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '>') { // >>
			opt[opt.size() - 1] += c;
			st.get();
			c = st.peek();
			if (c == '=') { // >>=
				opt[opt.size() - 1] += c;
				st.get();
				//return new pratt::token::RshAssign;
				return new pratt::token::Assign;
			}
			return new pratt::token::Rsh;
		}
		else if (c == '=') { // >=
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::GreaterThanEqual;
		}
		return new pratt::token::GreaterThan;
	}
	else if (c == '=') {
		opt[opt.size()] = c;
		st.get();
		c = st.peek();
		if (c == '=') { // ==
			opt[opt.size() - 1] += c;
			st.get();
			return new pratt::token::Equal;
		}
		return new pratt::token::Assign;
	}
	//===================== END OF OPERATORS =====================

	//=================== START OF DELIMITERS ====================
	else if (c == ';' || c == ',' || c == ' ' || c == '\t' || c == '\n' || c == '\r') {
		del[del.size()] = c;
		st.get();
		return Get();
	}
	//==================== END OF DELIMITERS =====================
	else {
		int ret;
		st >> ret;
		return new pratt::token::Integer(ret);
	}
}

void Lexer::PrintTokens() {
	int k = key.size();
	int i = ide.size();
	int l = lit.size();
	int o = opt.size();
	int d = del.size();

	std::cout << "TOKENS:\n\n";

	if (k > 0) {
		std::cout << "Number of keywords: " << k << "\n\n";
		for (int j = 0; j < k; j++) {
			std::cout << "key " << j + 1 << ": " << key[j] << std::endl;
		}
		std::cout << std::endl;
	}
	if (i > 0) {
		std::cout << "Number of identifiers: " << i << "\n\n";
		for (int j = 0; j < i; j++) {
			std::cout << "var " << j + 1 << ": " << ide[j] << std::endl;
		}
		std::cout << std::endl;
	}
	if (l > 0) {
		std::cout << "Number of literals: " << l << "\n\n";
		for (int j = 0; j < l; j++) {
			std::cout << "lit " << j + 1 << ": " << lit[j] << std::endl;
		}
		std::cout << std::endl;
	}
	if (o > 0) {
		std::cout << "Number of operators: " << o << "\n\n";
		for (int j = 0; j < o; j++) {
			std::cout << "opt " << j + 1 << ": " << opt[j] << std::endl;
		}
		std::cout << std::endl;
	}
	if (d > 0) {
		std::cout << "Number of delimiters: " << d << "\n\n";
		for (int j = 0; j < d; j++) {
			std::cout << "del " << j + 1 << ": ";

			if (del[j] == " ")
				std::cout << "whitespace\n";
			else if (del[j] == "\t")
				std::cout << "tab\n";
			else if (del[j] == "\n")
				std::cout << "EOL\n";
			else if (del[j] == "\r")
				std::cout << "carriage return\n";
			else
				std::cout << del[j] << std::endl;
		}
		std::cout << std::endl;
	}
}


} // namespace pratt
