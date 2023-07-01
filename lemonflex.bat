@echo off

tools\win_flex src\lexer.l
tools\lemon src\parser.y -q
move /Y lex.yy.c src\lex.yy.cpp
move /Y src\parser.c src\parser.cpp