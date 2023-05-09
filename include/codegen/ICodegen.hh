/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <node/Node.hh>

#include <string>

class ICodegen;
//class Linux_x64Codegen;
//class Linux_Arm64Codegen;
//class Mac_Arm64Codegen;
//class Mac_x64Codegen;
//class Win_x64Codegen;

namespace hive::ir {

class ICodegen {

	using Kind = NodeKinds;

	private:
		size idx = 0;

	protected:
		ProgNode* program;
		std::string instruction_bufffer;

	protected:

		auto check(i8 n, Kind kind) -> bool;
		auto check(Kind kind) -> bool;

		auto consume(Kind kind) -> Node*;

		auto peek(i8 n) -> Node*;
		auto peek() -> Node*;

		auto advance(i8 n) -> void;
		auto advance() -> void;


	public:
		const std::string name;

		ICodegen(const std::string name, ProgNode* program);

		virtual auto init() -> void = 0;

		virtual auto directive() -> void = 0;
		virtual auto label() -> void = 0;
		virtual auto instruction() -> void = 0;

		virtual auto add() -> void = 0;
		virtual auto sub() -> void = 0;
		virtual auto mul() -> void = 0;
		virtual auto div() -> void = 0;

		auto write(std::string target) -> void;


};

}
