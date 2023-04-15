#include "token/Token.hh"
#include <parse/Lex.hh>

namespace hive::ir {

Lex::Lex(const char* target, LexMode mode) {

}

auto Lex::scan_token() -> Token* {
	size start = idx;
	switch(peek()) {
		case '\n': {
			line   = line + 1;
			column = column = 1;
			return new Token(Kind::EOL, Pos(target, start, line, column, idx));
		}
		case '\t': return new Token(Kind::TAB, Pos(target, start, line, column, idx));
		case ' ': return new Token(Kind::SPACE, Pos(target, start, line, column, idx));
		case '\0': return new Token(Kind::_EOF, Pos(target, start, line, column, idx));
		case '-': {
			if (check(1, '>')) {
				advance();
				return new Token(Kind::RIGHT_ARROW, Pos(target, start, line, column, idx));
			}
			return new Token(Kind::DASH, Pos(target, start, line, column, idx));
		}
		case ':': return new Token(Kind::COLON, Pos(target, start, line, column, idx));
		case '#': return new Token(Kind::POUND, Pos(target, start, line, column, idx));
		case '|': return new Token(Kind::PIPE, Pos(target, start, line, column, idx));
		case '(': return new Token(Kind::OPEN_BRACE, Pos(target, start, line, column, idx));
		case ')': return new Token(Kind::CLOSE_PARAN, Pos(target, start, line, column, idx));
		case '{': return new Token(Kind::OPEN_BRACE, Pos(target, start, line, column, idx));
		case '}': return new Token(Kind::CLOSE_BRACE, Pos(target, start, line, column, idx));
		case '[': return new Token(Kind::OPEN_BRACKET, Pos(target, start, line, column, idx));
		case ']': return new Token(Kind::CLOSE_BRACKET, Pos(target, start, line, column, idx));
		case 'r': {
			std::string str = "";
			str.push_back(peek()); // eat the r
			for(;;) {
				if (!is_digit(1)) break; // break out if it's the next digit is not 0-9
																 //
				str.push_back(peek(1));
				advance();
			}
			return new Token(str, Kind::REGISTER, Pos(target, start, line, column, idx));
		}
		case 'd': {
			std::string str = "";
			str.push_back(peek()); // eat the r
			for(;;) {
				if (!is_digit(1)) break; // break out if it's the next digit is not 0-9
																 //
				str.push_back(peek(1));
				advance();
			}
			return new Token(str, Kind::DATA, Pos(target, start, line, column, idx));
		}
		default: {
		}
	}
}

auto Lex::peek(i8 n) -> char {
	return buffer[idx + n];
}

auto Lex::peek() -> char {
	return peek(0);
}

auto Lex::check(i8 n, char c) -> bool {
	return peek(n) == c;
}

auto Lex::check(char c) -> bool {
	return check(0, c);
}

auto Lex::advance(i8 n) -> void {
	idx = idx + n;
	line = line + n;
}

auto Lex::advance() -> void {
	advance(1);
}


auto Lex::is_hex() -> bool {return (peek() >= 'A' && peek() <= 'F') || (peek() >= 'a' && peek() <= 'f') || is_digit();}
auto Lex::is_digit() -> bool { return peek() >= '0' && peek() <= '9';}
auto Lex::is_digit(i8 n) -> bool { return peek(n) >= '0' && peek(n) <= '9';}
auto Lex::is_octal() -> bool {return peek() >= '0' && peek() <= '7';}
auto Lex::is_binary() -> bool {return (peek() == '0') || (peek() == '1');}

auto Lex::is_alpha() -> bool { return (peek() >= 'a' && peek() <= 'z') || (peek() >= 'A' && peek() <= 'Z'); }
auto Lex::is_alpha_num() -> bool { return is_alpha() || is_digit(); }
auto Lex::is_ident() -> bool{ return is_digit() || is_alpha() || check('_'); }

}
