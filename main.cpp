#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void getToken(string);
bool isDigit(char);
bool isLetter(char);
bool isSpace(char);
bool isSymbol(char);
string function(string s);
enum DFAstates { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
DFAstates state = START; //set START to be intial state

string RES_WORDS[] = { "if","then","else","begin","end","repeat","until","read","write","int","return" };

int main() {
	//reading sample tiny code from file
	ifstream file;
	string line, code, fileName;
	int flagLoop;
	while (1)
	{
		cout << "1-Scan tiny coden\nPlease enter number 1 for scan or any key to exit : ";
		cin >> flagLoop;
		if (flagLoop == 1)
		{
			cout << "Please enter file name : ";
			while (1)
			{
				cin >> fileName;
				if (fileName == "input.txt")
				{
					file.open(fileName);
					cout << "\n";
					break;
				}
				else
				{
					cout << "Name is not correct, Please enter the correct name : ";
				}
			}
			while (!file.eof())
			{
				getline(file, line);
				code += line + " ";
			}

			//writing scanner output to file
			freopen("output.txt", "w", stdout);
			getToken(code); // this is written to redir.txt

		}
		if (flagLoop != 1)
		{
			break;
		}
	}
	fclose(stdout);
	return 0;
}


void getToken(string l)
{
	string mytoken,BB;
	bool res_flag = 0;
	int i = 0;
	while (state != DONE) {
		switch (state) {
		case START:
			if (isSpace(l[i])) {
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else if (isDigit(l[i])) {
				state = INNUM;
			}
			else if (isLetter(l[i])) {
				state = INID;
			}
			else if (l[i] == ':') {
				state = INASSIGN;
			}
			else if (l[i] == '{') {
				i++;
				state = INCOMMENT;
			}
			else if (isSymbol(l[i])) {
				switch (l[i]) {
				case ';': cout << l[i] << " , SPECIAL SYMBOL" << endl; break;
				default: cout << l[i] << " , SPECIAL SYMBOL" << endl; break;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT) {
				while (l[i] != '}') {
					i++;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;

		case INNUM:

			while (isDigit(l[i])) {
				mytoken += l[i];
				i++;
			}
			if (1) {
				int nflag = 0;
				while (isLetter(l[i])) {
					mytoken += l[i];
					i++;
					nflag = 1;
				}
				if (nflag) {
					cout << mytoken << " , Error" << endl;
				}
				else
					cout << mytoken << " , number" << endl;
				mytoken = "";
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;

		case INID:
				while (isLetter(l[i]) || isDigit(l[i]) )  {
					mytoken += l[i];
					i++;
				}
				for (int i = 0; i < 11; i++)
				{
					if (RES_WORDS[i] == mytoken) res_flag = 1;
				}
				BB = function(mytoken);
				if (res_flag) cout << endl << mytoken << " , " << BB << " token" << endl;

				else {
					int digitflag = 0;
					for (int i = 0; i < mytoken.length(); i++)
					{
						if (isDigit(mytoken[i]))
						{
							digitflag = 1;
							break;
						}
					}
					if (digitflag)
						cout << mytoken << " , Error" << endl;
					else
						cout << mytoken << " , identifier" << endl;
					digitflag = 0;
				}
				mytoken = "";
				res_flag = 0;

				if (i == l.length()) state = DONE;
				else state = START;
				break;


		case INASSIGN:
			if (l[i] == ':') {
				i += 2;
				cout << ":=" <<" , ASSIGN"<< endl;
				state = START;
			}
			else {
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;
		case DONE:
			break;
		default :
			cout << "ERROR DETECTED" << endl;
		}
	}
}

bool isDigit(char d) { return (d >= '0' && d <= '9'); }

bool isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }

bool isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }

bool isSymbol(char c) { return (c == '+' || '-' || '*' || '/' || '=' || '<' || '(' || ')' || ';'); }

string function(string s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
	return s;
}
