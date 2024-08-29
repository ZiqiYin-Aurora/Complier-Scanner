
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/

#pragma once
#include <iostream>
#include <cstdlib>
#include<string>
using namespace std;

// token type
enum TokenType { ID, INDENT, DEDENT, ASSN, WHILE, IF, ELSE, ELIF, DEF, RETURN, AND, OR, NOT, INT, NUM, STR, ADD, SUB, MUL, DIV, LT, LTE, GT, GTE, EQT, DOT, LSB, RSB, LOP, ROP, NEWLINE, COL ,COM, COMMA, REM, ERROR, NEQ, EOP, TAB, SPACE};

struct Token {
	TokenType type;
	string str;
};

void printType(int i);
