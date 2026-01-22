#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

string keywords[] = {
    "int", "char", "float", "double", "return", "void", "long",
    "struct", "if", "else", "while", "for"
};

bool isKeyword(string s) {
    for (int i = 0; i < 12; i++)
        if (s == keywords[i])
            return true;
    return false;
}

bool isOperator(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='=' || c=='<'
           || c=='>' || c=='%';
}

bool isPunctuation(char c) {
    return c=='(' || c==')' || c=='{' || c=='}' || c==',' || c==';';
}

int main() {
    ifstream fin("input.c");
    char ch;
    string token;
    string symbolTable[50];
    int symCount = 0;
    int line = 1;

    cout << "\nTOKENS\n";

    while (fin.get(ch)) {

        if (ch == '\n') {
            line++;
            continue;
        }

        // Remove single-line comment
        if (ch == '/' && fin.peek() == '/') {
            while (fin.get(ch) && ch != '\n');
            line++;
            continue;
        }

        // Remove multi-line comment
        if (ch == '/' && fin.peek() == '*') {
            fin.get(ch);
            while (fin.get(ch)) {
                if (ch == '*' && fin.peek() == '/') {
                    fin.get(ch);
                    break;
                }
                if (ch == '\n') line++;
            }
            continue;
        }

        // Identifier or Keyword
        if (isalpha(ch)) {
            token = ch;
            while (isalnum(fin.peek())) {
                fin.get(ch);
                token += ch;
            }

            if (isKeyword(token)) {
                cout << "Keyword: " << token << endl;
            } else {
                cout << "Identifier: " << token << endl;
                symbolTable[symCount++] = token;
            }
        }

        // Constant
        else if (isdigit(ch)) {
            token = ch;
            while (isalnum(fin.peek())) {
                fin.get(ch);
                token += ch;
            }

            if (isalpha(token[token.length()-1])) {
                cout << "LEXICAL ERROR\nLine " << line
                     << " : " << token << " invalid lexeme\n";
            } else {
                cout << "Constant: " << token << endl;
            }
        }

        // Operator
        else if (isOperator(ch)) {
            cout << "Operator: " << ch << endl;
        }

        // Punctuation
        else if (isPunctuation(ch)) {
            cout << "Punctuation: " << ch << endl;
        }
    }

    cout << "\nSYMBOL TABLE ENTRIES\n";
    for (int i = 0; i < symCount; i++)
        cout << i+1 << ") " << symbolTable[i] << endl;

    fin.close();
    return 0;
}