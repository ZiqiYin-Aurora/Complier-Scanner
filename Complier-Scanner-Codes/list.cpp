
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/

#include "list.h"

LinkList::LinkList()
{
    tail = head = nullptr;
    size = 0;
}

/*Method to check if the list is empty**/
bool LinkList::isEmpty() const
{
    if (size == 0)
        return true;
    return false;
}

/*Method to push Token into link list**/
void LinkList::push(Token tk, int linenum)
{
    ListNode* newNode = new ListNode;
    newNode->token = tk;
    newNode->next = nullptr;
    newNode->prev = tail;
    newNode->lineNum = linenum;
    if (isEmpty()) {     // list is empty
        tail = newNode;
        head = tail;
    }
    else {      // only need to change tail when list is not empty
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

/*Method to pop the tail Node*/
Token LinkList::pop()
{
    Token tk;
    ListNode* Node = head->next;

    while (Node->next) {
        Node = Node->next;
    }
    tk = Node->token;

    return tk;
}

/*Method to display all the Tokens*/
void LinkList::display()
{
    ListNode* Node = head;
    cout<<endl;
    cout << "RESULT: \n";
    while (Node) {
        // Space will not be output
        if(Node->token.type!=SPACE){
            cout << Node->lineNum << " ";
            printType(Node->token.type);
            cout << " ";
            cout << Node->token.str << " " << endl;
        }
        Node = Node->next;
    }
}
