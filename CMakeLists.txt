cmake_minimum_required(VERSION 3.15)
project(c5)

add_executable(c5 
	src/main.cpp 
	src/vm.cpp
	src/lex.yy.cpp
)
