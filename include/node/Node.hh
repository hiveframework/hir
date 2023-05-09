/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#include <node/NodeKind.hh>
#include <token/Token.hh>
#include <vector>

namespace hive::ir {


class ProgNode;

class Node;

class VirtualRegisterNode;
class DataRegisterNode;
class DirectiveNode;

class IdentLiteralNode;
class StringLiteralNode;
class HexLiteralNode;
class DigitLiteralNode;
class OctalLiteralNode;
class BinaryLiteralNode;

class LabelNode;
class FuncNode;

class BiNode;

class NotNode;

class CompareNode;
class JumpNode;

class ReturnNode;
class DerefNode;
class PointerToNode;
class CallNode;
class StoreNode;
class WriteNode;
class DebugNode;
class DataStaticNode;
class DataStructNode;
class TypeNode;

class ProgNode {
	public:
		std::vector<Node*> nodes;

		ProgNode(std::vector<Node*> nodes) {
			this->nodes = nodes;
		}
};

class Node {
	public:
		using Kind = NodeKinds;

		Node(Kind kind);

	public:
		Kind kind;
		std::string node_name;
};

class VirtualRegisterNode : public Node {
	public:
		Token* ident;
		size id;

		VirtualRegisterNode(Token* ident, size id) : Node(Kind::VIRTUAL_REGISTER_NODE) {
			this->ident = ident;
			this->id    = id;
		}
};

class DataRegisterNode : public Node {
	public:
		Token* ident;
		size id;

		DataRegisterNode(Token* ident, size id) : Node(Kind::VIRTUAL_REGISTER_NODE) {
			this->ident = ident;
			this->id    = id;
		}
};

class DirectiveNode : public Node {
	public:
		Token* ident;
		Node* name;
		std::vector<Token*> tokens;

		DirectiveNode(Token* ident, Node* name, std::vector<Token*> tokens) : Node(Kind::DIRECTIVE_NODE) {
			this->ident  = ident;
			this->name   = name;
			this->tokens = tokens;
		}
};

class IdentLiteralNode : public Node {
	public:
		Token* ident;

		IdentLiteralNode(Token* ident) : Node(Kind::IDENT_LITERAL_NODE) {
			this->ident = ident;
		}
};

class StringLiteralNode : public Node {
	public:
		Token* start;
		Token* ident;
		Token* end;

		StringLiteralNode(Token* start, Token* ident, Token* end) : Node(Kind::STRING_LITERAL_NODE) {
			this->ident = ident;
		}
};

class HexLiteralNode : public Node {
	public:
		Token* ident;

		HexLiteralNode(Token* ident) : Node(Kind::HEX_LITERAL_NODE) {
			this->ident = ident;
		}
};

class DigitLiteralNode : public Node {
	public:
		Token* ident;

		DigitLiteralNode(Token* ident) : Node(Kind::HEX_LITERAL_NODE) {
			this->ident = ident;
		}
};

class OctalLiteralNode : public Node {
	public:
		Token* ident;

		OctalLiteralNode(Token* ident) : Node(Kind::HEX_LITERAL_NODE) {
			this->ident = ident;
		}
};

class BinaryLiteralNode : public Node {
	public:
		Token* ident;

		BinaryLiteralNode(Token* ident) : Node(Kind::HEX_LITERAL_NODE) {
			this->ident = ident;
		}
};

class LabelNode : public Node {
	public:
		Token* ident;
		Node* name;
		std::vector<Node*> instructions;

		LabelNode(Token* ident, Node* name, std::vector<Node*> instructions) : Node(Kind::LABEL_NODE) {
			this->ident = ident;
			this->name = name;
			this->instructions = instructions;
		}
};

class FuncNode : public Node {
	Token* ident;
	Token* name;
	std::vector<Node*> registers;

	public:
		FuncNode(Token* ident, Token* name, std::vector<Node*> registers) : Node(Kind::FUNCTION_NODE) {
			this->ident     = ident;
			this->name      = name;
			this->registers = registers;
		}
};

class BiNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		BiNode(Token* ident, Node* in_1, Node* in_2, Node* out, Kind kind) : Node(kind) {
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out;
		}
};

class NotNode : public Node {
	public:
		Token* ident;
		Node*  in;
		Node*  out;

		NotNode(Token* ident, Node* in, Node* out) : Node(Kind::NOT_NODE){
			this->ident = ident;
			this->in    = in;
			this->out   = out ;
		}
};

//Note(anita): A catch all for all the compare node types
class CompareNode : public Node {
	public:
		Token* ident;
		Node* in_1;
		Node* in_2;

		CompareNode(Token* ident, Node* in_1, Node* in_2, Kind kind) : Node(kind) {
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
		}
};

//Note(anita): A catch all for all the jump node types
class JumpNode : public Node {
	public:
		Token* ident;
		Node* in_1;
		Node* in_2;

		JumpNode(Token* ident, Node* in_1, Node* in_2, Kind kind) : Node(kind) {
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
		}
};

class ReturnNode : public Node {
	public:
		Token* ident;
		Node* reg;

		ReturnNode(Token* ident, Node* reg) : Node(Kind::RETURN_NODE) {
			this->ident = ident;
			this->reg   = reg;
		}
};

class DerefNode : public Node {
	public:
		Token* ident;
		Node* reg;
		Node* out;

		DerefNode(Token* ident, Node* reg, Node* out) : Node(Kind::DEREF_NODE) {
			this->ident = ident;
			this->reg   = reg;
			this->out   = out;
		}
};

class PointerToNode : public Node {
	public:
		Token* ident;
		Node* reg;
		Node* out;

		PointerToNode(Token* ident, Node* reg, Node* out) : Node(Kind::DEREF_NODE) {
			this->ident = ident;
			this->reg   = reg;
			this->out   = out;
		}
};

class CallNode : public Node {
	public:
		Token* ident;
		Node* lib;
		Node* function;
		std::vector<Node*> params;

		CallNode(Token* ident, Node* lib, Node* function, std::vector<Node*> params) : Node(Kind::CALL_NODE) {
			this->ident    = ident;
			this->lib      = lib;
			this->function = function;
			this->params   = params;
		}
};

class StoreNode : public Node {
	public:
		Token* ident;
		Node* value;
		Node* reg;

		StoreNode(Token* ident, Node* value, Node* reg) : Node(Kind::STORE_NODE) {
			this->ident = ident;
			this->value = value;
			this->reg   = reg;
		}
};

class WriteNode : public Node {

	public:
		Token* ident;
		Node* value;
		Node* reg;

		WriteNode(Token* ident, Node* value, Node* reg) : Node(Kind::WRITE_NODE) {
			this->ident = ident;
			this->value = value;
			this->reg   = reg;
		}
};

class DataStaticNode : public Node {
	public:
		Node* data_register;
		Token* start;
		std::vector<Node*> types;
		Token* end;

		DataStaticNode(Node* d_reg, Token* start, std::vector<Node*> types, Token* end) : Node(Kind::DATA_STATIC_NODE){
			this->data_register = d_reg;
			this->start         = start;
			this->types         = types;
			this->end           = end;
		}
};

class DataStructNode : public Node {
	public:
		Node* data_register;
		Token* ident;
		Node* literal;

		DataStructNode(Node* data_register, Token* ident, Node* literal) : Node(Kind::DATA_STATIC_NODE) {
			this->data_register = data_register;
			this->ident         = ident;
			this->literal       = literal;
		}
};

class TypeNode : public Node {
	public:
		Token* ident;

		TypeNode(Token* ident, Kind kind) : Node(kind) {
			this->ident = ident;
		}
};
}
