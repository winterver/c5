cmake_minimum_required(VERSION 3.15)
project(c5)

add_executable(c5 
	src/main.cpp 
	src/lex.yy.cpp
	src/parser.cpp
	src/codegen.cpp
	#src/vm.cpp
)

target_compile_options(c5 PRIVATE /wd4005)
