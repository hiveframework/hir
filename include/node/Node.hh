/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#include <node/NodeKind.hh>
#include <token/Token.hh>

namespace hive::ir {

class Node;

class VirtualRegisterNode;
class DataRegisterNode;
class LiteralNode;

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

class VirtualRegisterNode : Node {
	public:
		Token* ident;
		size number;

		VirtualRegisterNode(Token* ident, size number) : Node(Kind::VIRTUAL_REGISTER_NODE) {
			this->ident  = ident;
			this->number = number;
		}
};

class DataRegisterNode : Node {
	public:
		Token* ident;
		size number;

		DataRegisterNode(Token* ident, size number) : Node(Kind::VIRTUAL_REGISTER_NODE) {
			this->ident  = ident;
			this->number = number;
		}
};

}
