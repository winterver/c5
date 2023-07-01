cmake_minimum_required(VERSION 3.15)
project(c5)

add_executable(c5 
	src/parser.cpp # main() is here
	src/lex.yy.cpp
	src/symtab.cpp
)
