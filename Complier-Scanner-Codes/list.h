
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/

#pragma once
#include <iostream>
#include <cstdlib>
#include<string>
#include "token.h"
using namespace std;

struct ListNode {
	Token token;
	struct ListNode* next;
	struct ListNode* prev;
	int lineNum;
};


class LinkList {
private:
	//ListNode* head;
	ListNode* tail;
	int size;

public:
    ListNode* head;
	LinkList();					// Constructor
	bool isEmpty()const;	// Determine whether the list is empty
	void push(Token tk, int linensum);	// Append a Token into the List
	Token pop();				// Pop a Token
	void display();			// Print out all the Tokens
};

