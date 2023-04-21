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

class AddNode;
class SubNode;
class DivNode;
class MulNode;
class AndNode;
class OrNode;
class XorNode;
class NotNode;
class LabelNode;
class CompareEqualityNode;
class CompareLessThanNode;
class CompareGreaterThanNode;
class JumpIfNode;
class JumpNotEqualNode;
class JumpEqualNode;
class FunctionNode;
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

class Node {
	public:
		using Kind = NodeKinds;

		Node(Kind kind) {
			this->kind = kind;
		}

		auto get_node_kind() -> Kind {return kind;}
		auto get_node_name() -> std::string {return name_from_node(kind);}

	private:
		Kind kind;
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
		Token* ident;

		StringLiteralNode(Token* ident) : Node(Kind::STRING_LITERAL_NODE) {
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

class TypeNode : public Node {
	public:
		Token* ident;

		TypeNode(Token* ident, Kind kind) : Node(kind) {
			this->ident = ident;
		}
};

class AddNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		AddNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::ADD_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
		}
};

class SubNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		SubNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::SUB_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
		}
};

class DivNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		DivNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::DIV_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
		}
};

class MulNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		MulNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::MUL_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
		}
};

class AndNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		AndNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::AND_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
		}
};

class XorNode : public Node {
	public:
		Token* ident;
		Node*  in_1;
		Node*  in_2;
		Node*  out;

		XorNode(Token* ident, Node* in_1, Node* in_2, Node* out) : Node(Kind::XOR_NODE){
			this->ident = ident;
			this->in_1  = in_1;
			this->in_2  = in_2;
			this->out   = out ;
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
}
