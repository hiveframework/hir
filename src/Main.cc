#include <parse/Parse.hh>

#include <fmt/core.h>


using namespace hive::ir;

auto main(int argc, char** argv) -> int {
	Lex lex(argv[1], LexMode::TEXT);
	Parse parse(lex);

	auto files = parse.construct();

	For (files->nodes) {
		fmt::println("b");
		fmt::println("{}", it->node_name);
	}

	return 0;
}
