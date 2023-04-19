#include <parse/Lex.hh>

#include <fmt/core.h>

using namespace hive::ir;

auto main(int argc, char** argv) -> int {
	Lex lex(argv[1], LexMode::TEXT);

	For(lex.tokens) {
		fmt::println("{}",it->to_string());
	}
	return 0;
}
