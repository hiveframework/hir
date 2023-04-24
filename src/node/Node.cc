#include <node/Node.hh>

namespace hive::ir {

Node::Node(Kind kind) {
	this->kind = kind;

	//Hack(anita): Hack to get node names working
	For (node_name_map) {
		if (kind == it.first) {
			this->node_name = it.second;
		}
	}
}
}
