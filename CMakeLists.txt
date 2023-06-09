cmake_minimum_required(VERSION 3.20)

project(hir)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor/fmt)

include_directories(include)

set(HIR_SRC
	src/Main.cc

	src/parse/Lex.cc
	src/parse/Parse.cc

	src/token/Token.cc
	src/token/TokenKind.cc

	src/node/NodeKind.cc
	src/node/Node.cc

	src/codegen/ICodegen.cc

	src/codegen/MacArm64Codegen.cc
)

add_definitions( -DDEBUG=1)

add_executable(${PROJECT_NAME} ${HIR_SRC})

target_link_libraries(${PROJECT_NAME} fmt::fmt)

