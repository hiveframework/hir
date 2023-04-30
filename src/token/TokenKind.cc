/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <token/TokenKind.hh>

namespace hive::ir {

const std::map<TokenKind, std::string> token_kind_name_map = {
	#define Tok(kind, name) {TokenKind::kind, name},
		TOKEN_TYPES_LIST
	#undef Tok
};

auto name_from_kind(TokenKind kind) -> std::string {
	For(token_kind_name_map) {
		if (it.first == kind) {
			return it.second;
		}
	}
	return "IDENT_LITERAL";
}

auto kind_from_name(std::string name) -> TokenKind {
	For(token_kind_name_map) {
		if (it.second == name) {
			return it.first;
		}
	}
	return TokenKind::IDENT_LITERAL;
}

}
