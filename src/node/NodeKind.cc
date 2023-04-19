/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <node/NodeKind.hh>
namespace hive::ir {

auto name_from_node(NodeKinds kind) -> std::string {
	For(node_name_map) {
		if (it.first == kind) {
			return it.second;
		}
	}
	return "INVALID";
}

auto node_from_name(std::string name) -> NodeKinds {
	For(node_name_map) {
		if (it.second == name) {
			return it.first;
		}
	}
	return NodeKinds::INVALID;
}

}
