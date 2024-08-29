
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include<string>
#include<stack>
#include "list.h"
#include "token.h"
#include "automata.h"

using namespace std;


LinkList* list = new LinkList();
stack<int> space; // stack to store each line's space in the front


/*Method to generate INDENT or DEDENT, and push into the link list**/
void indentation(string s, int& i, int count) {
	Token tk;
    Token tk_null;
    int space_count = 0; //use to count the number of space.
    string s1=s;
    
    bool emptyLine = true; //if it is an empty line
    
    for (char &c : s){
        // ascii: 13 for CR(carriage return)
        if (c == '\t' || c == ' ' || c == 13 || c == '\r' || c == '\n'){
            continue; //if empty line
        }
        else if(c=='#')
            break; //if comment line
        else
            emptyLine = false;
    }
    
    
    // if the line is not empty (have a token except SPACE or TAB)
    if(emptyLine == false){
        //count spaces in the front
        for (; i < s.length(); i++) {
            if (s[i] == ' ') {
                space_count++;
            }
            if (s[i] != ' ') {
                break;
            }
        }
        //push space count into stack and generate INDENT
        if(space_count > space.top()){
            space.push(space_count);
            tk.type = INDENT;
            list->push(tk, count);
        }
        //pop and generate DEDENT
        else{
            while(space_count < space.top()){
                space.pop();
                tk.type = DEDENT;
                list->push(tk, count);
            }
            //if align error happens
            if(space_count != space.top()){
                tk.type=ERROR;
                tk.str = "Align error to match Indent and Dedent!!!";
                list->push(tk, count);
            }
        }
    }

}


/*Method to read pym file and then invoke DFA and other methods to generate tokens**/
void ReadDataFromFileLBLIntoString()
{
    string filename; //the file name
	string s;   //store the txt line by line
	Token tk;
	int count = 1; // which is to record the line number.
	
	cout << ":) Hello,what is the name of the Pym source file?" << endl;
    cout << ">>> ";
	cin >> filename;
	ifstream fin;

	fin.open(filename); //open file
    // Determine if the file is open successfully
	if (!fin.is_open()) {
		cout << ":) Error opening " << filename << endl;
		exit(1);
	}
	else {
        cout << ":) Open successfully!"<<endl;
        cout << ":) The tokens in your file are as fllows:"<<endl;
		while (getline(fin, s))
		{
            
            int i = 0; //index of char in a line
            
			//cout << count << " " << s << endl;
            
            // generate INDENT/DEDENT
            indentation(s, i, count);
            
			// Output other Tokens
			for (; i < s.length(); ) {
                tk = DFA(s, i);
                list->push(tk, count);
			}
            
            // NewLine Token
            tk.type = NEWLINE;
            tk.str = "\n";
            list->push(tk,count);
            count++;
		}
	}

}

/*Method to detect Error: Spaces/Tab in the beginning of the program */
void Detect_Space_Error(){
    ListNode* Node = list->head; //begin check from the head of list
    
    while (Node) {
        // to find the first token that is the begin keyword of program
        // then look the if last one is a SPACE/TAB/INDENT, which are not allowed in Pym
        if(Node->token.type!=COM && Node->token.type!=NEWLINE && Node->token.type!=SPACE && Node->token.type!=TAB && Node->token.type!=INDENT)
        {
            cout<<endl;
            ListNode* Pre_node = Node->prev; // the last token
            if(Pre_node->token.type==SPACE || Pre_node->token.type==TAB || Pre_node->token.type==INDENT){
                Pre_node->token.type = ERROR;
                Pre_node->token.str = "Tab or Space cannot in the beginning of a line!";
                break;
            }
            else
                break;
        }
        
        Node = Node->next;
    }
}

int main() {
    
    space.push(0);
	ReadDataFromFileLBLIntoString(); // read file and generate token list
    Detect_Space_Error(); // detect Error: spaces in the beginning of lines
    list->display();
    
}
