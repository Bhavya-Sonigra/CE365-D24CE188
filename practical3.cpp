#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_set>
#include <vector>

using namespace std;

const unordered_set<string> kKeywords = {
    "int", "char", "float", "double", "return", "void", "long",
    "struct", "if", "else", "while", "for"
};

bool isKeyword(const string &s) {
    return kKeywords.find(s) != kKeywords.end();
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' ||
           c == '>' || c == '%';
}

bool isPunctuation(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == ',' || c == ';';
}

int main() {
    ifstream fin("input.c");
    if (!fin.is_open()) {
        cout << "Could not open input.c" << endl;
        return 1;
    }

    char ch;
    string token;
    vector<string> symbolTable;
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
            while (isalnum(fin.peek()) || fin.peek() == '_') {
                fin.get(ch);
                token += ch;
            }

            if (isKeyword(token)) {
                cout << "Keyword: " << token << endl;
            } else {
                cout << "Identifier: " << token << endl;
                symbolTable.push_back(token);
            }
        }

        // Constant
        else if (isdigit(ch)) {
            token = ch;
            while (isalnum(fin.peek()) || fin.peek() == '_') {
                fin.get(ch);
                token += ch;
            }

            bool hasAlpha = false;
            for (char c : token) {
                if (isalpha(static_cast<unsigned char>(c)) || c == '_') {
                    hasAlpha = true;
                    break;
                }
            }

            if (hasAlpha) {
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
    for (size_t i = 0; i < symbolTable.size(); i++) {
        cout << i + 1 << ") " << symbolTable[i] << endl;
    }

    fin.close();
    return 0;
}