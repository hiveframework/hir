/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <parse/Lex.hh>
#include <node/Node.hh>

#include <err/ErrorCodes.hh>

namespace hive::ir {

class Parse {
	private:
		using Kind  = TokenKind;
		using Error = ErrorCode;
		Lex& lex;
		size idx;

	public:
		Parse(Lex& lex);

		auto construct() -> ProgNode*;

	private:
		auto groups() -> Node*;
		auto instruction() -> Node*;

		auto literal() ->	Node*;

		auto directive() -> Node*;

		auto reg() -> Node*;
		auto v_register() -> Node*;
		auto d_register() -> Node*;

		auto type() -> Node*;

		auto lable() -> Node*;

		auto bi_node() -> Node*;
		auto compare() -> Node*;
		auto jump() -> Node*;
		auto _not() -> Node*;
		auto _return() -> Node*;
		auto de_ref() -> Node*;
		auto ptr_to() -> Node*;
		auto call() -> Node*;
		auto store() -> Node*;
		auto write() -> Node*;

	private:
		auto advance(i8 n) -> void;
		auto advance() -> void;

		auto peek(i8 n) -> Token*;
		auto peek() -> Token*;

		auto check(i8 n, Kind kind) -> bool;
		auto check(Kind kind) -> bool;

		auto consume(Kind kind) -> Token*;

		auto not_impl(std::string msg) -> void;
		auto parse_error(std::string name) -> void;
};

}
