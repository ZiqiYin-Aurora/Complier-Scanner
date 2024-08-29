
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/

#pragma once
#include <iostream>
#include <cstdlib>
#include<string>
#include "list.h"
#include "token.h"

extern LinkList* list; //global variable, to store all the tokens in a list

enum State { START, DONE, DONE_IMM, WRONG, WAIT_OVER, COMMENT, IN_ID, IN_NUM, READ_POS, READ_NEG, READ_GT, READ_LT, READ_NEQ, READ_EQT };

Token DFA(string inputString, int& i);
