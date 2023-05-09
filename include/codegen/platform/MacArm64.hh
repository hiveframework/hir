/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once


#include <codegen/ICodegen.hh>

namespace hive::ir {

	class MacArm64 : public ICodegen {
	public:
		explicit MacArm64(ProgNode* program);

		auto init() -> void override;
		auto directive() -> void override;
		auto label() -> void override;
		auto instruction() -> void override;

		auto add() -> void override;
		auto sub() -> void override;
		auto mul() -> void override;
		auto div() -> void override;

	private:
		auto create_label() -> void;
		auto create_instruction() -> void;
};

}
