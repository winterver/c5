@echo off

tools\win_flex src\lexer.l
tools\win_bison src\parser.y -o y.tab.c -H
move /Y lex.yy.c src\lex.yy.cpp
move /Y y.tab.c src\y.tab.cpp
move /Y y.tab.h src\y.tab.h
