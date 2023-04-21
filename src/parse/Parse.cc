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

auto Parse::instruction() -> Node* {
	switch(peek()->kind) {
		case Kind::ADD: not_impl("ADD");
		case Kind::DATA: return d_register();
		case Kind::SUBTRACT: not_impl("SUBTRACT");
		case Kind::DIVIDE: not_impl("DIVIDE");
		case Kind::MULTIPLY: not_impl("MULTIPLY");
		case Kind::AND: not_impl("AND");
		case Kind::OR: not_impl("OR");
		case Kind::XOR: not_impl("XOR");
		case Kind::COMPARE_EQUALITY: not_impl("COMPARE_EQUALITY");
		case Kind::COMPARE_GREATER_THAN: not_impl("COMPARE_GREATER_THAN");
		case Kind::COMPARE_LESS_THAN: not_impl("COMPARE_GREATER_THAN");
		case Kind::JUMP: not_impl("JUMP");
		case Kind::JUMP_IF: not_impl("JUMP_IF");
		case Kind::JUMP_NOT_EQUAL: not_impl("JUMP_NOT_EQUAL");
		case Kind::RETURN: not_impl("RETURN");
		case Kind::DEREF: not_impl("DEREF");
		case Kind::POINTERTO: not_impl("POINTERTO");
		case Kind::CALL: not_impl("CALL");
		case Kind::STORE: not_impl("STORE");
		case Kind::WRITE: not_impl("WRITE"); //Question(anita): should we rename this to load that makes more sense to me?
		case Kind::_DEBUG: not_impl("DEBUG");
		case Kind::STATIC: not_impl("STATIC");

		default:
			parse_error(fmt::format("Illegal token found {}", peek()->to_string()));
	}
	return nullptr;
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
