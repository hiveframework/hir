/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <parse/Parse.hh>

namespace hive::ir {

Parse::Parse(Lex& lex) : lex(lex) {}

auto Parse::init_parse() -> Node* {
	while (check(Kind::_EOF)) {
		switch(peek()->kind) {
			case Kind::POUND: return directive();
			case Kind::LABEL: not_impl("LABEL");
			case Kind::FUNCTION: not_impl("FUNCTION");
		}
	}
	return nullptr;
};


auto Parse::lable() -> Node* {
	auto ident = consume(Kind::LABEL);
	consume(Kind::SPACE);
	auto name = literal();
	consume(Kind::COLON);
	consume(Kind::EOL);

	std::vector<Node*> lables;
	while(!check(Kind::TAB)) {
		consume(Kind::TAB);
		auto inst = instruction();
		consume(Kind::EOL);
	}

	return new LabelNode(ident, name, lables);
}

auto Parse::instruction() -> Node* {
	switch(peek()->kind) {
		case Kind::ADD: return bi_node();
		case Kind::DATA: return d_register();
		case Kind::SUBTRACT: return bi_node();
		case Kind::DIVIDE: return bi_node();
		case Kind::MULTIPLY: return bi_node();
		case Kind::AND: return bi_node();
		case Kind::OR: return bi_node();
		case Kind::XOR: return bi_node();
		case Kind::NOT: return _not();
		case Kind::COMPARE_EQUALITY: return compare();
		case Kind::COMPARE_GREATER_THAN: return compare();
		case Kind::COMPARE_LESS_THAN: return compare();
		case Kind::JUMP: return jump();
		case Kind::JUMP_IF: return jump();
		case Kind::JUMP_NOT_EQUAL: return jump();
		case Kind::RETURN: return  _return();
		case Kind::DEREF: return de_ref();
		case Kind::POINTERTO: return ptr_to();
		case Kind::CALL: return call();
		case Kind::STORE: return store();
		case Kind::WRITE: return write();
		case Kind::_DEBUG: {
				parse_error("DEBUG is not implemented!");
		};
		case Kind::STATIC: not_impl("STATIC");

		default:
			parse_error(fmt::format("Illegal token found {}", peek()->to_string()));
	}
	return nullptr;
}

auto Parse::literal() -> Node* {
	if (!peek()->is_literal()) parse_error("Expected a literal");

	if (check(Kind::IDENT_LITERAL)) {
		auto ident = consume(Kind::IDENT_LITERAL);
		return new IdentLiteralNode(ident);
	}

	if (check(Kind::STRING_LITERAL)) {
		auto ident = consume(Kind::STRING_LITERAL);
		return new StringLiteralNode(peek());
	}

	if (check(Kind::HEX_LITERAL)) {
		auto ident = consume(Kind::HEX_LITERAL);
		return new HexLiteralNode(ident);
	}

	if (check(Kind::DIGIT_LITERAL)) {
		auto ident = consume(Kind::DIGIT_LITERAL);
		return new DigitLiteralNode(ident);
	}

	if (check(Kind::OCTAL_LITERAL)) {
		auto ident = consume(Kind::OCTAL_LITERAL);
		return new OctalLiteralNode(ident);
	}

	if (check(Kind::BINARY_LITERAL)) {
		auto ident = consume(Kind::BINARY_LITERAL);
		return new BinaryLiteralNode(ident);
	}

	parse_error(fmt::format("Unable to lex literal got {} instead!", peek()->to_string()));
	return nullptr;
}

auto Parse::directive() -> Node* {
	auto ident = consume(Kind::POUND);
	auto lit   = literal();
	std::vector<Token*> nodes;

	while (!check(Kind::EOL)) {
		nodes.push_back(peek());
		advance();
	}

	return new DirectiveNode(ident, lit, nodes);
}

auto Parse::reg() -> Node* {
	if (!peek()->is_register()) parse_error(fmt::format("Expexted a register got {} instead", peek()->to_string()));

	if (check(Kind::REGISTER)) return v_register();
	if (check(Kind::DATA)) return d_register();

	parse_error(fmt::format("Impossed parse for register for token {}.", peek()->to_string()));
	return nullptr;
}

auto Parse::v_register() -> Node* {
	auto reg = consume(Kind::REGISTER);
	auto str = reg->name;
	auto id_str = str.substr(1);
	size id = std::stoi(id_str);

	return new VirtualRegisterNode(reg, id);
}

auto Parse::d_register() -> Node* {
	auto reg = consume(Kind::DATA);
	auto str = reg->name;
	auto id_str = str.substr(1);
	size id = std::stoi(id_str);

	return new VirtualRegisterNode(reg, id);
}

auto Parse::type() -> Node* {
	auto ident = peek();
	if (!ident->is_type()) parse_error(fmt::format("Token is not type {}", ident->to_string()));
	advance();

	if (ident->kind == Kind::I8) return new TypeNode(ident, NodeKinds::I8_TYPE_NODE);
	if (ident->kind == Kind::I16) return new TypeNode(ident, NodeKinds::I16_TYPE_NODE);
	if (ident->kind == Kind::I32) return new TypeNode(ident, NodeKinds::I32_TYPE_NODE);
	if (ident->kind == Kind::I64) return new TypeNode(ident, NodeKinds::I64_TYPE_NODE);

	parse_error(fmt::format("Impossible token error for looking for type got {} instead.", ident->to_string()));
	return nullptr;
}

/**
 * Parse out all the bi nodes
 * ADD
 * SUBTRACT
 * DIVIDE
 * MULTIPLY
 * AND
 * OR
 * XOR
 */
auto Parse::bi_node() -> Node* {
	auto ident = peek();
	if (!ident->is_bi_instruction()) parse_error(fmt::format("Expected a Bi instruction got {} instead", ident->to_string()));

	advance();
	consume(Kind::SPACE);
	auto in_1 = reg();
	consume(Kind::COMMA);
	consume(Kind::SPACE);
	auto in_2 = reg();
	consume(Kind::SPACE);
	consume(Kind::RIGHT_ARROW);
	consume(Kind::SPACE);
	auto out = v_register();
	if (ident->kind == Kind::ADD) return new BiNode(ident, in_1, in_2, out, NodeKinds::ADD_NODE);
	if (ident->kind == Kind::SUBTRACT) return new BiNode(ident, in_1, in_2, out, NodeKinds::SUB_NODE);
	if (ident->kind == Kind::DIVIDE) return new BiNode(ident, in_1, in_2, out, NodeKinds::DIV_NODE);
	if (ident->kind == Kind::MULTIPLY) return new BiNode(ident, in_1, in_2, out, NodeKinds::MUL_NODE);
	if (ident->kind == Kind::AND) return new BiNode(ident, in_1, in_2, out, NodeKinds::AND_NODE);
	if (ident->kind == Kind::OR) return new BiNode(ident, in_1, in_2, out, NodeKinds::OR_NODE);
	if (ident->kind == Kind::XOR) return new BiNode(ident, in_1, in_2, out, NodeKinds::XOR_NODE);

	parse_error(fmt::format("Impossible parse for binary instruction got {}.", ident->to_string()));

	return nullptr;
}

/**
 * Parse out the comparioson nodes
 *
 * COMPARE_GREATER_THAN
 * COMPARE_EQUALITY
 * COMPARE_LESS_THAN
 */
auto Parse::compare() -> Node* {
	auto ident = peek();
	if (!ident->is_compare()) parse_error(fmt::format("{{}} \n\t is not a comparioson node", ident->name));

	consume(Kind::SPACE);
	auto in_1 = reg();
	consume(Kind::COMMA);
	consume(Kind::SPACE);
	auto in_2 = reg();

	if (ident->kind == Kind::COMPARE_EQUALITY) return new CompareNode(ident, in_1, in_2, NodeKinds::COMPARE_EQUALITY_NODE);
	if (ident->kind == Kind::COMPARE_GREATER_THAN) return new CompareNode(ident, in_1, in_2, NodeKinds::COMPARE_GREATER_THAN_NODE);
	if (ident->kind == Kind::COMPARE_LESS_THAN) return new CompareNode(ident, in_1, in_2, NodeKinds::COMPARE_LESS_THAN_NODE);

	parse_error(fmt::format("Impossible token found for comparision identifer -> {}", ident->to_string()));
	return nullptr;
}

/**
 * JUMP
 * JUMP_EQUAL
 * JUMP_IF
 * JUMP_NOT_EQUAL
 */
auto Parse::jump() -> Node* {
	auto ident = peek();
	if (!ident->is_jump()) parse_error(fmt::format("{{}} \n\t is not a jump node", ident->name));

	consume(Kind::SPACE);
	auto in_1 = reg();
	consume(Kind::COMMA);
	consume(Kind::SPACE);
	auto in_2 = reg();

	if (ident->kind == Kind::JUMP) return new JumpNode(ident, in_1, in_2, NodeKinds::JUMP_NODE);
	if (ident->kind == Kind::JUMP_EQUAL) return new JumpNode(ident, in_1, in_2, NodeKinds::JUMP_EQUAL_NODE);
	if (ident->kind == Kind::JUMP_IF) return new JumpNode(ident, in_1, in_2, NodeKinds::JUMP_IF_NODE);
	if (ident->kind == Kind::JUMP_NOT_EQUAL) return new JumpNode(ident, in_1, in_2, NodeKinds::JUMP_NOT_EQUAL_NODE);

	parse_error(fmt::format("Impossible token found for comparision identifer -> {}", ident->to_string()));
	return nullptr;
}

auto Parse::_not() -> Node* {
	auto ident = consume(Kind::NOT);
	consume(Kind::SPACE);

	auto in = reg();

	consume(Kind::SPACE);
	consume(Kind::RIGHT_ARROW);
	consume(Kind::SPACE);

	auto out = reg();

	return new NotNode(ident, in, out);
}

auto Parse::_return() -> Node* {
	auto ident = consume(Kind::RETURN);
	consume(Kind::SPACE);
	auto target = reg();
	return new ReturnNode(ident, target);
}

auto Parse::de_ref() -> Node* {
	auto ident = consume(Kind::DEREF);

	consume(Kind::SPACE);

	auto in = reg();

	consume(Kind::SPACE);
	consume(Kind::RIGHT_ARROW);
	consume(Kind::SPACE);

	auto out = reg();

	return new DerefNode(ident, in, out);
}

auto Parse::ptr_to() -> Node* {
	auto ident = consume(Kind::POINTERTO);

	consume(Kind::SPACE);
	auto in = reg();
	consume(Kind::SPACE);
	auto out = reg();

	return new PointerToNode(ident, in, out);
}

auto Parse::call() -> Node* {
	auto ident = consume(Kind::CALL);

	consume(Kind::SPACE);
	auto lib = literal();
	consume(Kind::DOT);
	auto func = literal();

	std::vector<Node*> params;
	params.push_back(reg());


	for(;;) {
		if (check(Kind::EOL)) break;
		consume(Kind::COMMA);
		params.push_back(reg());
	}

	return new CallNode(ident, lib, func, params);
}

auto Parse::store() -> Node* {
	auto ident = consume(Kind::STORE);

	consume(Kind::SPACE);

	auto value = reg();

	consume(Kind::SPACE);
	consume(Kind::RIGHT_ARROW);
	consume(Kind::SPACE);

	auto out = reg();
	return new StoreNode(ident, value, out);
}

auto Parse::write() -> Node* {
	auto ident = consume(Kind::WRITE);

	consume(Kind::SPACE);

	auto value = reg();

	consume(Kind::SPACE);
	consume(Kind::RIGHT_ARROW);
	consume(Kind::SPACE);

	auto out = reg();
	return new WriteNode(ident, value, out);
}

auto Parse::advance(i8 n) -> void { idx = idx + n; }
auto Parse::advance() -> void { advance(1); }

auto Parse::peek(i8 n) -> Token* {return lex.tokens.at(idx + n);}
auto Parse::peek() -> Token* { return peek(1); }

auto Parse::check(i8 n, Kind kind) -> bool { return kind == peek(n)->kind; }
auto Parse::check(Kind kind) -> bool { return check(1, kind); }

auto Parse::consume(Kind kind) -> Token* {
	if (!check(kind)) parse_error(fmt::format("Expected kind of {} got {}  for token {}",name_from_kind(kind), name_from_kind(peek()->kind), peek()->to_string()));

	auto ident = peek();
	advance();
	return ident;
}

auto Parse::not_impl(std::string msg) -> void {
	fmt::println("Not implemented: {}", msg);
	std::exit(Error::NOT_IMPLEMENTED);
}

auto Parse::parse_error(std::string msg) -> void {
	fmt::println("Parse Error: {}", msg);
	std::exit(ErrorCode::PARSE_ERROR);
}

}
