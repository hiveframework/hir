/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
  */
#pragma once

#include <token/TokenKind.hh>

namespace hive::ir {

struct Pos {
	std::string path;
	size offset_start;
	size line;
	size column;
	size offset_end;;
	size len;

	Pos(std::string path, size offset_start, size line, size column, size offset_end);

	auto to_string() -> std::string;
};

class Token {
	using Kind = TokenKind;

	public:
		Token(std::string name, Kind kind, Pos pos);
		Token(std::string name, Pos pos);
		Token(Kind kind, Pos pos);

	public:
		std::string name;
		Kind kind;
		Pos pos;

		auto is_literal() -> bool;
		auto is_instruction() -> bool;
		auto is_bi_instruction() -> bool;

		auto is_type() -> bool;

		auto is_register() -> bool;
		auto is_compare() -> bool;
		auto is_jump() -> bool;
		auto to_string() -> std::string;
		auto short_to_string() -> std::string;
};

}
