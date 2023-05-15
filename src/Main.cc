#include <parse/Parse.hh>

#include <fmt/core.h>


using namespace hive::ir;

auto main(int argc, char** argv) -> int {
	auto lex = new Lex(argv[1], LexMode::TEXT);
	Parse parse(lex);

	auto files = parse.construct();

//	For(files->nodes) {
//		if (it->kind == NodeKinds::DIRECTIVE_NODE) {
//			DebugInfo(it->to_string())
//			DebugInfo("\n")
//		}
//
//		if (it->kind == NodeKinds::LABEL_NODE) {
//			DebugInfo(it->to_string())
//			auto lbs = (LabelNode*)it;
//				For(lbs->instructions) {
//					DebugInfo(fmt::format("\t{}", it->to_string()))
//				}
//			}
//	}

	return 0;
}
