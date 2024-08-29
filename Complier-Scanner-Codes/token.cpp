#include "token.h"

void printType(int i)
{
	switch (i) {
	case 0: cout << "ID"; break;
	case 1: cout << "INDENT"; break;
	case 2: cout << "DEDENT"; break;
	case 3: cout << "ASSN"; break;
	case 4: cout << "WHILE"; break;
	case 5: cout << "IF"; break;
	case 6: cout << "ELSE"; break;
	case 7: cout << "ELIF"; break;
	case 8: cout << "DEF"; break;
	case 9: cout << "RETURN"; break;
	case 10: cout << "AND"; break;
	case 11: cout << "OR"; break;
	case 12: cout << "NOT"; break;
	case 13: cout << "INT"; break;
	case 14: cout << "NUM"; break;
	case 15: cout << "STR"; break;
	case 16: cout << "ADD"; break;
	case 17: cout << "SUB"; break;
	case 18: cout << "MUL"; break;
	case 19: cout << "DIV"; break;
	case 20: cout << "LT"; break;
	case 21: cout << "LTE"; break;
	case 22: cout << "GT"; break;
	case 23: cout << "GTE"; break;
	case 24: cout << "EQT"; break;
	case 25: cout << "DOT"; break;
	case 26: cout << "LSB"; break;
	case 27: cout << "RSB"; break;
	case 28: cout << "LOP"; break;
	case 29: cout << "ROP"; break;
	case 30: cout << "NEWLINE"; break;
	case 31: cout << "COL"; break;
	case 32: cout << "COM"; break;
	case 33: cout << "COMMA"; break;
	case 34: cout << "REM"; break;
    case 35: cout << "ERROR"; break;
    case 36: cout << "NEQ"; break;
    case 37: cout << "EOP"; break;
    case 38: cout << "TAB"; break;

	default: cout << " ";
	}
}


