/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <codegen/platform/MacArm64.hh>

namespace hive::ir {

MacArm64::MacArm64(ProgNode* program): ICodegen("MacArm64", program) {

}

auto MacArm64::init() -> void {
}
auto MacArm64::directive() -> void {}
auto MacArm64::label() -> void {}
auto MacArm64::instruction() -> void {}

auto MacArm64::add() -> void {}
auto MacArm64::sub() -> void {}
auto MacArm64::mul() -> void {}
auto MacArm64::div() -> void {}


}
