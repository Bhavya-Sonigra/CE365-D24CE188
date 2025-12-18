#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    int n = s.length();

    if (n < 2) {
        cout << "Invalid String" << endl;
        return 0;
    }

    if (s[n-2] != 'b' || s[n-1] != 'b') {
        cout << "Invalid String" << endl;
        return 0;
    }

    for (int i = 0; i < n-2; i++) {
        if (s[i] != 'a') {
            cout << "Invalid String" << endl;
            return 0;
        }
    }

    cout << "Valid String" << endl;
    return 0;
}