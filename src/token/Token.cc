/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <token/Token.hh>

namespace hive::ir {

Pos::Pos(std::string path, size offset_start, size line, size column, size offset_end) {
	this->path = path;
	this->offset_start = offset_start;
	this->line = line;
	this->column = column;
	this->offset_end = offset_end;
	this->len = this->offset_end - this->offset_start;
}

Token::Token(std::string name, Kind kind, Pos pos) : name(name), kind(kind), pos(pos) {}

Token::Token(std::string name, Pos pos): name(name), kind(kind_from_name(name)), pos(pos) {}

Token::Token(Kind kind, Pos pos) : kind(kind), name(name_from_kind(kind)), pos(pos) {}

}
