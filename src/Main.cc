#include <parse/Parse.hh>

#include <fmt/core.h>


using namespace hive::ir;

auto main(int argc, char** argv) -> int {
	auto lex = new Lex(argv[1], LexMode::TEXT);
	Parse parse(lex);

	auto files = parse.construct();

	return 0;
}
