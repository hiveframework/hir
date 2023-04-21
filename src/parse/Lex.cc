#include <token/Token.hh>
#include <parse/Lex.hh>

#include <fmt/core.h>

#include <cstdlib>
#include <cstdio>

namespace hive::ir {

Lex::Lex(const char* target, LexMode mode) {
	load_target(target);

	//Hack(anita): Added this here because version must be at the top of this and this is a look ahead
	if (check(0,'#')) {
		tokens.push_back(new Token(Kind::POUND, Pos(target, idx, line, column, idx)));
	} else {
		lex_error("Must start with a version directive");
	}

	while (peek() != '\0') {
		auto token = scan_token();
		tokens.push_back(token);
		advance();
	}
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
			if (check(2, '>')) {
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
			advance();
			for(;;) {
				if (!is_digit()) break; // break out if it's the next digit is not 0-9
				advance();
			}
			idx--; // ugly hack to restore the state
			return new Token(str, Kind::REGISTER, Pos(target, start, line, column, idx));
		}
		case 'd': {
			std::string str = "";
			str.push_back(peek()); // eat the r
			advance();
			for(;;) {
				if (!is_digit()) break; // break out if it's the next digit is not 0-9

				str.push_back(peek());
				advance();
			}
			idx--; // ugly hack to restor the state
			return new Token(str, Kind::DATA, Pos(target, start, line, column, idx));
		}
		case '"': {
			tokens.push_back(new Token(Kind::DOUBLE_QUOTE, Pos(target, start, line, column, idx)));
			advance();

			auto local_start = idx;
			std::string str = concat_string();
			tokens.push_back(new Token(str,Kind::STRING_LITERAL, Pos(target, local_start, line, column, idx)));

			if (!check('"')) {
				lex_error("Expected a '\"' and failed");
			}
			return new Token(Kind::DOUBLE_QUOTE, Pos(target, idx, line, column, idx));
		}
		case '.': return new Token(Kind::DOT, Pos(target, start, line, column, idx));
		default: {
			if (is_digit()) {
				return concat_number();
			} else if (is_alpha_num()) {
				return concat_ident();
			} else {
				lex_error(fmt::format("invalid token being lexed '{}' @ {}:{}", peek(), line, column));
			}
		}
	}
	return nullptr;
}

auto Lex::concat_string() -> std::string  {
	std::string str = "";

	while(peek() != '"') {
		str.push_back(peek());
		advance();
	}
	return str;
}

auto Lex::concat_number() -> Token* {
	std::string str = "";
	size start = idx;
	bool has_dot = false;

	if (check('0')) {
		str.push_back(peek());
		advance();
		if (check('x')) {
			str.push_back(peek());
			advance();
			while(is_hex()) {
				str.push_back(peek());
				advance();
				return new Token(str, Kind::HEX_LITERAL, Pos(target, start, line, column, idx));
			}
		} else if (check('b')) {
			str.push_back(peek());
			advance();
			while(is_binary()) {
				str.push_back(peek());
				advance();
				return new Token(str, Kind::BINARY_LITERAL, Pos(target, start, line, column, idx));
			}

		} else if (check('o')) {
			str.push_back(peek());
			advance();
			while(is_octal()) {
				str.push_back(peek());
				advance();
				return new Token(str, Kind::OCTAL_LITERAL, Pos(target, start, line, column, idx));
			}
		}
	}

	while (is_alpha() || check('.')) {
		if (check('.')) {
			if (has_dot == false) {
				has_dot = true;
				str.push_back(peek());
				advance();
			} else {
				lex_error("To many dots in float literal");
			}
		}

		str.push_back(peek());
		advance();
	}

	if (has_dot) {
		return new Token(str, Kind::FLOAT_LITERAL, Pos(target, start, line, column, idx));
	} else {
		return new Token(str, Kind::DIGIT_LITERAL, Pos(target, start, line, column, idx));
	}
}

auto Lex::concat_ident() -> Token* {
	std::string str = "";
	size start = idx;

	while (is_alpha_num()) {
		str.push_back(peek());
		advance();
	}
	idx--;//Note(anita):  A gross hack I know but I don't care 4/14/2023
	return new Token(str, Kind::IDENT_LITERAL, Pos(target, start, line, column, idx));
}

auto Lex::peek(i8 n) -> char { return buffer[idx + n];}
auto Lex::peek() -> char { return peek(1); }

auto Lex::check(i8 n, char c) -> bool { return peek(n) == c;}
auto Lex::check(char c) -> bool { return check(1, c); }

auto Lex::advance(i8 n) -> void {
	idx = idx + n;
	line = line + n;
}

auto Lex::advance() -> void { advance(1); }

auto Lex::is_hex() -> bool {return (peek() >= 'A' && peek() <= 'F') || (peek() >= 'a' && peek() <= 'f') || is_digit();}
auto Lex::is_digit() -> bool { return peek() >= '0' && peek() <= '9';}
auto Lex::is_octal() -> bool {return peek() >= '0' && peek() <= '7';}
auto Lex::is_binary() -> bool {return (peek() == '0') || (peek() == '1');}

auto Lex::is_alpha() -> bool { return (peek() >= 'a' && peek() <= 'z') || (peek() >= 'A' && peek() <= 'Z'); }
auto Lex::is_alpha_num() -> bool { return is_alpha() || is_digit() || check('_'); }
auto Lex::is_ident() -> bool{ return check('_') || is_digit() || is_alpha(); }

auto Lex::lex_error(std::string msg) -> void {
	fmt::println("Lex Error: {}", msg);
	std::exit(-1);
}


auto Lex::load_target(const char* f) -> void {

	std::FILE* fptr;
	fptr = std::fopen(f, "r");

	if (!fptr) {
		lex_error(fmt::format("No file {} found", target));
	}
	size buffer_size;

	std::fseek(fptr, 0L, SEEK_END);
	buffer_size = std::ftell(fptr);
	std::rewind(fptr);

	buffer = (char*)std::calloc(1, buffer_size + 1);

	if (!buffer) {
		std::fclose(fptr);
		std::free(buffer);
		lex_error("Unable to allocate memry to char buffer");
	}

	if (1 != std::fread(buffer, buffer_size, 1, fptr)) {
		std::fclose(fptr);
		std::free(buffer);
		lex_error(fmt::format("Failed to read {}", target));
	}

	std::fclose(fptr);

}

}
