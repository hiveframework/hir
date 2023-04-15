/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#include <Defs.hh>
#include <token/Token.hh>

#include <vector>

namespace hive::ir {

enum class LexMode : u8 {
	TEXT,
	BINARY,
};

class Lex {
	using Kind = TokenKind;

	public:
		std::vector<Token*> token;

		Lex(const char* target, LexMode mode);
	private:
		std::string target;
		char* buffer;
		size idx;
		size line = 1;
		size column = 1;
	private:
		auto peek(i8 n) -> char;
		auto peek() -> char;

		auto check(i8 n, char c) -> bool;
		auto check(char c) -> bool;

		auto advance(i8 n) -> void;
		auto advance() -> void;

		auto scan_token() -> Token*;

	private:
		auto is_hex() -> bool;
		auto is_digit() -> bool;
		auto is_digit(i8 n) -> bool;
		auto is_octal() -> bool;
		auto is_binary() -> bool;

		auto is_alpha() -> bool;
		auto is_alpha_num() -> bool;
		auto is_ident() -> bool;

};

}
