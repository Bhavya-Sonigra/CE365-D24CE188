#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;

    if (s.length() < 2) {
        cout << "Invalid String";
        return 0;
    }

    if (s[s.length() - 2] != 'b' || s[s.length() - 1] != 'b') {
        cout << "Invalid String";
        return 0;
    }

    for (int i = 0; i < s.length() - 2; i++) {
        if (s[i] != 'a') {
            cout << "Invalid String";
            return 0;
        }
    }

    cout << "Valid String";
    return 0;
}