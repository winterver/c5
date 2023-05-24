@echo off

tools\win_flex src\lexer.l
move /Y lex.yy.c src\lex.yy.cpp
