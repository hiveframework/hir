/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <Defs.hh>
#include <map>

namespace hive::ir {

#define NODE_KIND_NAME_LIST \
	_Node(INVALID, "INVALID") \
	_Node(BI_NODE_START, "") \
		_Node(ADD_NODE, "ADD_NODE") \
		_Node(SUB_NODE, "SUB_NODE") \
		_Node(DIV_NODE, "DIV_NODE") \
		_Node(MUL_NODE, "MUL_NODE") \
		_Node(AND_NODE, "AND_NODE") \
		_Node(OR_NODE,  "OR_NODE") \
		_Node(XOR_NODE, "XOR_NODE") \
	_Node(BI_NODE_END, "") \
\
	_Node(NOT_NODE, "NOT_NODE") \
	_Node(LABEL_NODE, "LABEL_NODE") \
	_Node(COMPARE_EQUALITY_NODE, "COMPARE_EQUALITY_NODE") \
	_Node(COMPARE_LESS_THAN_NODE, "COMPARE_LESS_THAN_NODE") \
	_Node(COMPARE_GREATER_THAN_NODE, "COMPARE_GREATER_THAN_NODE") \
	_Node(JUMP_NODE, "JUMP_IF_NODE") \
	_Node(JUMP_IF_NODE, "JUMP_IF_NODE") \
	_Node(JUMP_NOT_EQUAL_NODE, "JUMP_NOT_EQUAL_NODE") \
	_Node(JUMP_EQUAL_NODE, "JUMP_EQUAL_NODE") \
	_Node(FUNCTION_NODE, "FUNCTION_NODE") \
	_Node(RETURN_NODE, "RETURN_NODE") \
	_Node(DEREF_NODE, "DEREF_NODE") \
	_Node(POINTER_TO_NODE, "POINTER_TO_NODE") \
	_Node(CALL_NODE, "CALL_NODE") \
	_Node(STORE_NODE, "STORE_NODE") \
	_Node(WRITE_NODE, "WRITE_NODE") \
	_Node(DEBUG_NODE, "DEBUG_NODE") \
	_Node(DATA_STATIC_NODE, "DATA_STATIC_NODE") \
	_Node(DATA_STRUCT_NODE, "DATA_STRUCT_NODE") \
\
	_Node(LITERAL_NODE_START, "") \
		_Node(STRING_LITERAL_NODE, "STRING_LITERAL_NODE") \
		_Node(IDENT_LITERAL_NODE, "IDENT_LITERAL_NODE") \
		_Node(BINARY_LITERAL_NODE, "BINARY_LITERAL_NODE") \
		_Node(FLOAT_LITERAL_NODE, "FLOAT_LITERAL_NODE") \
		_Node(HEX_LITERAL_NODE, "HEX_LITERAL_NODE") \
		_Node(DIGIT_LITERAL_NODE, "DIGIT_LITERAL_NODE") \
		_Node(OCTAL_LITERAL_NODE, "OCTAL_LITERAL_NODE") \
	_Node(LITERAL_NODE_END, "") \
\
	_Node(TYPE_NODE_START, "") \
		_Node(I8_TYPE_NODE, "I8_TYPE_NODE") \
		_Node(I16_TYPE_NODE, "I16_TYPE_NODE") \
		_Node(I32_TYPE_NODE, "I32_TYPE_NODE") \
		_Node(I64_TYPE_NODE, "I64_TYPE_NODE") \
	_Node(TYPE_NODE_END, "") \
\
	_Node(VIRTUAL_REGISTER_NODE, "VIRTUAL_REGISTER_NODE") \
	_Node(DATA_REGISTER_NODE, "REGISTER_NODE") \
	_Node(DIRECTIVE_NODE, "DIRECTIVE_NODE") \

}

enum class NodeKinds : u8 {
	#define _Node(kind, name) kind,
		NODE_KIND_NAME_LIST
	#undef _Node
};

const std::map<NodeKinds, std::string> node_name_map =  {
	#define _Node(kind, name) {NodeKinds::kind, name},
		NODE_KIND_NAME_LIST
	#undef _Node
};
