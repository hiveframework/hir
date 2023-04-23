/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with thistoken
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <Defs.hh>

//Note(anita): Maybe impl this ourselves to avoid templates same with all the vector stuff
//             Or do we just wait till we to a language rewrite in minerva?
#include <map>
#include <string>

namespace hive::ir {

#define TOKEN_TYPES_LIST \
	Tok(TAB, "TAB") \
	Tok(SPACE, "SPACE") \
	Tok(EOL, "EOL") \
	Tok(COMMENT, "COMMENT") \
	Tok(_EOF, "EOF") \
	Tok(RIGHT_ARROW, "RIGHT_ARROW") \
	Tok(DASH, "DASH") \
	Tok(COLON, "COLON") \
	Tok(COMMA, "COMMA") \
	Tok(DOT, "DOT") \
	Tok(POUND, "POUND") \
	Tok(PIPE, "PIPE") \
	Tok(DOUBLE_QUOTE, "DOUBLE_QUOTE") \
\
	Tok(REISTER_START, "") \
		Tok(REGISTER, "REGISTER") \
		Tok(DATA, "DATA_REGISTER") \
	Tok(REISTER_END, "") \
\
	Tok(SCOPE_START, "") \
		Tok(OPEN_PARAN, "(") \
		Tok(CLOSE_PARAN, ")") \
		Tok(OPEN_BRACE, "{") \
		Tok(CLOSE_BRACE, "}") \
		Tok(OPEN_BRACKET, "[") \
		Tok(CLOSE_BRACKET, "]") \
	Tok(SCOPE_END, "") \
\
	Tok(LITERAL_START, "") \
		Tok(IDENT_LITERAL, "IDENT_LITERAL") \
		Tok(STRING_LITERAL, "STRING_LITERAL") \
		Tok(HEX_LITERAL, "HEX_LITERAL") \
		Tok(DIGIT_LITERAL, "DIGIT_LITERAL") \
		Tok(FLOAT_LITERAL, "FLOAT_LITERAL") \
		Tok(OCTAL_LITERAL, "OCTAL_LITERAL") \
		Tok(BINARY_LITERAL, "BINARY_LITERAL") \
	Tok(LITERAL_END, "") \
\
	Tok(GROUP_START, "") \
		Tok(LABEL, "LABEL") \
		Tok(FUNCTION, "FUNCTION") \
	Tok(GROUP_END, "") \
\
	Tok(INSTRUCTION_START, "") \
		Tok(BI_INSTRUCTION_START, "") \
			Tok(ADD, "ADD") \
			Tok(SUBTRACT, "SUBTRACT") \
			Tok(DIVIDE, "DIVIDE") \
			Tok(MULTIPLY, "MULTIPLY") \
			Tok(AND, "AND") \
			Tok(OR, "OR") \
			Tok(XOR, "XOR") \
		Tok(BI_INSTRUCTION_END, "") \
\
		Tok(NOT, "NOT") \
\
		Tok(COMPARE_START, "") \
			Tok(COMPARE_EQUALITY, "COMPARE_EQUALITY") \
			Tok(COMPARE_LESS_THAN, "COMPARE_LESS_THAN") \
			Tok(COMPARE_GREATER_THAN, "COMPARE_GREATER_THAN") \
		Tok(COMPARE_END, "") \
\
		Tok(JUMP_START, "") \
			Tok(JUMP, "JUMP") \
			Tok(JUMP_IF, "JUMP_IF") \
			Tok(JUMP_NOT_EQUAL, "JUMP_NOT_EQUAL") \
			Tok(JUMP_EQUAL, "JUMP_EQUAL") \
		Tok(JUMP_END, "") \
\
		Tok(RETURN, "RETURN") \
		Tok(DEREF, "DEREF") \
		Tok(POINTERTO, "POINTERTO") \
		Tok(CALL, "CALL") \
		Tok(STORE, "STORE") \
		Tok(WRITE, "WRITE") \
		Tok(_DEBUG, "DEBUG") \
		Tok(STATIC, "STATIC") \
	Tok(INSTRUCTION_END, "") \
\
	Tok(TYPE_START ,"") \
	Tok(I8, "i8") \
	Tok(I16, "i16") \
	Tok(I32, "i32") \
	Tok(I64, "i64") \
	Tok(TYPE_END, "") \

enum class TokenKind {
	#define Tok(kind, name) kind,
		TOKEN_TYPES_LIST
	#undef Tok
};

const std::map<TokenKind, std::string> token_kind_name_map = {
	#define Tok(kind, name) {TokenKind::kind, name},
		TOKEN_TYPES_LIST
	#undef Tok
};

auto name_from_kind(TokenKind kind) -> std::string;
auto kind_from_name(std::string name) -> TokenKind;

}
