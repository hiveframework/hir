/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <codegen/ICodegen.hh>

#include <fmt/core.h>

#include <cstdio>


namespace hive::ir {

ICodegen::ICodegen(const std::string name, ProgNode* program) : name(name), program(program) {}

auto ICodegen::check(i8 n, Kind kind) -> bool {
	return peek(n)->kind == kind;
}

auto ICodegen::check(Kind kind) -> bool {
	return check(1, kind);
}

auto ICodegen::consume(Kind kind) -> Node* {
	if (check(kind)) {
		auto node = peek();
		advance();
		return node;
	}
	return nullptr;
}

auto ICodegen::peek(i8 n) -> Node* {
	return program->nodes.at(idx + n);
}

auto ICodegen::peek() -> Node* {
	return peek(1);
}

auto ICodegen::advance(i8 n) -> void {
	this->idx = idx + n;
}

auto ICodegen::advance() -> void {
	advance(1);
}

auto ICodegen::write(std::string target) -> void {
	std::FILE *file = std::fopen(target.c_str(), "w");

	if (!file) {
		std::free(file);
		fmt::println("Unable to write file");
		std::exit(-3);
	}
	std::fprintf(file, "%s", instruction_bufffer.c_str());
	std::fclose(file);
}

}
