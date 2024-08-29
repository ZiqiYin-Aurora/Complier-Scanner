
/*GROUP INFORMATION:
 殷子祺 YIN, ZIQI  1809853D-I011-0160
 杨霁渲 YANG, JIXUAN  1809853U-I011-0093**/

#include "automata.h"
using namespace std;


Token DFA(string s, int &i)
{
    Token tk;   //use to store each token produced by DFA.
    string num="";  //store number especially signed number like +7, -3\5
    string word=""; //store word include ID or keywords
    string str="";  //store string between ” and ”(include “”), e.g. “dog is cute” sentence will be stored into the str
    string warning="!!Unknown character in pym: ";
    string ascii=" ASCII: ";
    State currentState = START; //initialization of the State
    
    while (i<s.length()){
        if (currentState == DONE ||
            currentState == DONE_IMM ||
            currentState == WRONG){
            return tk;
            break;
        }

        if (currentState == START) {
            // Handle Spaces
            if(s[i]=='\t'){
                tk.type = TAB;
                i=i+1;
                currentState = DONE_IMM;
            }
            else if (s[i]==' ' || s[i]=='\r' || s[i]=='\n') {
                tk.type=SPACE;
                currentState = DONE_IMM;
                i = i + 1;
             }
            
            //BASIC SIGN 
            else if (s[i] == '+') {
                currentState = READ_POS; 
                num.append(1, s[i]);
                i = i + 1;
            }
            else if (s[i] == '-') {
                currentState = READ_NEG;
                num.append(1, s[i]);
                i = i + 1;
            }
            else if (s[i] == '*') {
                tk.type = MUL;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == '/') {
                tk.type = DIV;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == '%') {
                tk.type = REM;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == ':') {
                tk.type = COL;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == '[') {
                tk.type = LSB;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == ']') {
                tk.type = RSB;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == '(') {
                tk.type = LOP;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == ')') {
                tk.type = ROP;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == ',') {
                tk.type = COMMA;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == '.') {
                tk.type = DOT;
                i = i + 1;
                currentState = DONE_IMM;
            }
            else if (s[i] == EOF) {
                tk.type = EOP;
                i = i + 1;
                currentState = DONE_IMM;
            }
            
            //READ >
            else if (s[i] == '>') {
                currentState = READ_GT;
                i = i + 1;
            }
            //READ <
            else if (s[i] == '<') {
                currentState = READ_LT;
                i = i + 1;
            }
            //READ !
            else if (s[i] == '!') {
                currentState = READ_NEQ;
                i = i + 1;
            }
            //READ =
            else if (s[i] == '=') {
                currentState = READ_EQT;
                i = i + 1;
            }
            //READ COMMENT
            else if (s[i] == '#') {
                currentState = COMMENT;
                tk.type = COM;
                i = s.length();
            }
            //READ "
            else if (s[i] == '"') {
                currentState = WAIT_OVER;
                str.append(1, s[i]);
                i = i + 1;
            }

            // DIGIT start reading a num
            else if (isdigit(s[i])) {
                num.append(1, s[i]);
                currentState = IN_NUM;
                i = i + 1;
            }
            // LETTER start reading the letter
            else if (isalpha(s[i])||s[i]=='_') {
                word.append(1, s[i]);
                currentState = IN_ID;
                i = i + 1;
            }
            else {
                tk.type = ERROR;
                string ch="";
                ch.append(1,s[i]); //append the ERROR character
                ascii+=to_string((int)s[i]); //append the ascii code of the ERROR character
                tk.str=warning+ch+ascii;
                currentState = WRONG;
                i = i + 1;
            }
        }

        // STR
        if (currentState == WAIT_OVER) {
            int position = s.find("\"", i );
            if (position!=s.npos) {
                str.append(s, i, position-i+1);
                i = position+1;
                tk.type = STR;
                tk.str = str;
                currentState = DONE;
            }
            else {
                tk.type = ERROR;
                tk.str = "Not a STR! The quotation mark in front is not matched.";
                currentState = WRONG;
            }
        }
        
        // READ_POS 
        if (currentState == READ_POS) {
            Token last_tk = list->pop();
            if (last_tk.type != NUM && last_tk.type != ID && isdigit(s[i])) { // +3\7  (+ 3\7)
                num.append(1, s[i]);
                currentState = IN_NUM;
                i = i + 1;
            }
            // ERROR if case: +>  +-  ++(no incerment in pym)
            else if((last_tk.type != NUM && last_tk.type != ID && last_tk.type != SPACE && last_tk.type != STR) && (!isdigit(s[i]) && !isalpha(s[i]) && s[i]!=' ')){
                tk.type = ERROR;
                string ch="";
                ch.append(1,s[i-1]);
                ch.append(1,s[i]); //append the ERROR characters
                tk.str=warning+ch;
                currentState = WRONG;
                i=i+1;
            }
            else { // 5 + 19 or "str1" +"str2" or i+j or j+1 or 1+j
                tk.type = ADD; 
                currentState = DONE; 
            } 
        }

        // READ_NEG 
        if (currentState == READ_NEG) {
            Token last_tk = list->pop();
            if (last_tk.type != NUM && last_tk.type != ID && isdigit(s[i])) { // -3\7
                num.append(1,s[i]);
                currentState = IN_NUM;
                i = i + 1;
            }
            // ERROR if case: ->  --  -+
            else if((last_tk.type != NUM && last_tk.type != ID && last_tk.type != SPACE) && (!isdigit(s[i]) && !isalpha(s[i]) && s[i]!=' ')){
                tk.type = ERROR;
                string ch="";
                ch.append(1,s[i-1]);
                ch.append(1,s[i]); //append the ERROR characters
                tk.str=warning+ch;
                currentState = WRONG;
                i=i+1;
            }
            else { // 5 - 19
                tk.type = SUB;
                currentState = DONE;
            }
        }

        // IN_NUM read number consecutively
        if (currentState == IN_NUM) {
            if (isdigit(s[i])||s[i]=='\\') { // num, includes the form 3\7
                num.append(1, s[i]);
                currentState = IN_NUM;
                i = i + 1;
            }
            else {
                tk.str = num; 
                tk.type = NUM;
                currentState = DONE_IMM;
                // do not change the index position. 
            }
        }

        // IN_ID read letter consecutively
        if (currentState == IN_ID) {
            if (isalpha(s[i])||isdigit(s[i])||s[i]=='_') {
                word.append(1, s[i]);
                currentState = IN_ID;
                i = i + 1;
            }
            else {
                // Keywords
                if (word == "while") {
                    tk.type = WHILE; 
                }
                else if (word == "if") {
                    tk.type = IF;
                }
                else if (word == "else") {
                    tk.type = ELSE;
                }
                else if (word == "elif") {
                    tk.type = ELIF;
                }
                else if (word == "def") {
                    tk.type = DEF;
                }
                else if (word == "return") {
                    tk.type = RETURN;
                    tk.str = "return";
                    currentState = DONE_IMM;

                }
                else if (word == "and") { //logical and
                    tk.type = AND;
                }
                else if (word == "or") { //logical or
                    tk.type = OR;
                }
                else if (word == "not") { //logical not
                    tk.type = NOT;
                }
                else if (word == "int") {
                    tk.type = INT;
                }
                else if (word == "num") {
                    tk.type = NUM;
                }
                else if (word == "str") {
                    tk.type = STR;
                }       
                // ID
                else {
                    tk.str = word;
                    tk.type = ID;
                    currentState = DONE_IMM;

                }
               
                currentState = DONE_IMM;
                // do not change the index position. 
            }
        }

        // READ_GT
        if (currentState == READ_GT) {
            Token last_tk = list->pop();
            if (s[i] == '=') {
                currentState = DONE;
                i = i + 1;
                tk.type = GTE;
            }
            // ERROR if case: >+  >:
            else if((last_tk.type != NUM && last_tk.type != ID && last_tk.type != SPACE) && (!isdigit(s[i]) && !isalpha(s[i]) && s[i]!=' ')){
                tk.type = ERROR;
                string ch="";
                ch.append(1,s[i-1]);
                ch.append(1,s[i]); //append the ERROR characters
                tk.str=warning+ch;
                currentState = WRONG;
                i=i+1;
            }
            else {
                currentState = DONE_IMM;
                tk.type = GT;
                // do not change index. 
            }
        }

        // READ_LT
        if (currentState == READ_LT) {
            Token last_tk = list->pop();
            if (s[i] == '=') {
                currentState = DONE;
                i = i + 1;
                tk.type = LTE;
            }
            // ERROR if case: <+  <:
            else if((last_tk.type != NUM && last_tk.type != ID && last_tk.type != SPACE) && (!isdigit(s[i]) && !isalpha(s[i]) && s[i]!=' ')){
                tk.type = ERROR;
                string ch="";
                ch.append(1,s[i-1]);
                ch.append(1,s[i]); //append the ERROR characters
                tk.str=warning+ch;
                currentState = WRONG;
                i=i+1;
            }
            else {
                currentState = DONE_IMM;
                tk.type = LT;
                // do not change index. 
            }
        }

        //READ_NEQ
          if (currentState == READ_NEQ) {
           if (s[i] == '=') {
               tk.type = NEQ;
               currentState = DONE;
               i=i+1;
           }
           else {
               tk.type = ERROR;
               string ch="";
               ch.append(1,s[i-1]);
               tk.str=warning+ch;
               currentState = WRONG;
           }
          }
        
        // READ_EQT
        if (currentState == READ_EQT) {
            if (s[i] == '=') {
                currentState = DONE;
                i = i + 1;
                tk.type = EQT;
            }
            else {
                currentState = DONE_IMM;
                tk.type = ASSN;
                // do not change index. 
            }
        }
    }


    return tk;
}
