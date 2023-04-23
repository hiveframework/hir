/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <token/Token.hh>
#include <fmt/core.h>

namespace hive::ir {

Pos::Pos(std::string path, size offset_start, size line, size column, size offset_end) {
	this->path = path;
	this->offset_start = offset_start;
	this->line = line;
	this->column = column;
	this->offset_end = offset_end;
	this->len = this->offset_end - this->offset_start;
}

auto Pos::to_string() -> std::string {
	return fmt::format("Pos{{path={}, offset_start={}, line={}, column={}, offset_end={}, len={}}}", path, offset_start, line, column, offset_end, len);
}

Token::Token(std::string name, Kind kind, Pos pos) : name(name), kind(kind), pos(pos) {}

Token::Token(std::string name, Pos pos): name(name), kind(kind_from_name(name)), pos(pos) {}

Token::Token(Kind kind, Pos pos) : kind(kind), name(name_from_kind(kind)), pos(pos) {}

auto Token::is_literal() -> bool { return (Kind::LITERAL_START < kind && kind < Kind::LITERAL_END); }
auto Token::is_type() -> bool { return (Kind::TYPE_START < kind && kind < Kind::TYPE_END); }
auto Token::is_instruction() -> bool { return (Kind::INSTRUCTION_START < kind && kind < Kind::INSTRUCTION_END); }
auto Token::is_bi_instruction() -> bool { return (Kind::BI_INSTRUCTION_START < kind && kind < Kind::BI_INSTRUCTION_END); }
auto Token::is_register() -> bool { return (Kind::REISTER_START < kind && kind < Kind::REISTER_END); }
auto Token::is_compare() -> bool { return (Kind::COMPARE_START < kind && kind < Kind::COMPARE_END); }
auto Token::is_jump() -> bool { return (Kind::JUMP_START < kind && kind < Kind::JUMP_END); }

auto Token::to_string() -> std::string {
	return fmt::format("Token{{name={}, kind={}, {}}}", name, name_from_kind(kind), pos.to_string());
}

}
