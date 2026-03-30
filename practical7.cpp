#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cctype>

using namespace std;

map<char, set<char>> first, follow;
map<char, vector<string>> grammar;
vector<char> nonTerminals;

bool isNonTerminal(char c) {
    return isupper(static_cast<unsigned char>(c)) != 0;
}

set<char> firstOfString(const string &rhs, size_t start) {
    set<char> result;
    bool allNullable = true;

    for (size_t i = start; i < rhs.length(); i++) {
        char sym = rhs[i];
        if (!isNonTerminal(sym)) {
            result.insert(sym);
            allNullable = false;
            break;
        }

        bool nullable = false;
        for (char f : first[sym]) {
            if (f == 'e') {
                nullable = true;
            } else {
                result.insert(f);
            }
        }
        if (!nullable) {
            allNullable = false;
            break;
        }
    }

    if (allNullable) {
        result.insert('e');
    }

    return result;
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    set<char> ntSet;
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        if (input.length() < 3) {
            cout << "Invalid production format" << endl;
            return 1;
        }

        char lhs = input[0];
        size_t rhsStart = (input[1] == '-' && input.length() >= 3 && input[2] == '>') ? 3 : 2;
        if (rhsStart >= input.length()) {
            cout << "Invalid production format" << endl;
            return 1;
        }

        string rhs = input.substr(rhsStart);
        grammar[lhs].push_back(rhs);
        if (ntSet.find(lhs) == ntSet.end()) {
            ntSet.insert(lhs);
            nonTerminals.push_back(lhs);
        }
    }

    // FIRST sets (fixed-point)
    bool changed = true;
    while (changed) {
        changed = false;
        for (char nt : nonTerminals) {
            for (const string &rhs : grammar[nt]) {
                set<char> rhsFirst = firstOfString(rhs, 0);
                for (char c : rhsFirst) {
                    if (first[nt].insert(c).second) {
                        changed = true;
                    }
                }
            }
        }
    }

    // FOLLOW sets (fixed-point)
    if (!nonTerminals.empty()) {
        follow[nonTerminals[0]].insert('$');
    }

    changed = true;
    while (changed) {
        changed = false;
        for (const auto &entry : grammar) {
            char lhs = entry.first;
            for (const string &rhs : entry.second) {
                for (size_t i = 0; i < rhs.length(); i++) {
                    char cur = rhs[i];
                    if (!isNonTerminal(cur)) {
                        continue;
                    }

                    set<char> betaFirst = firstOfString(rhs, i + 1);
                    bool epsilonInBeta = betaFirst.find('e') != betaFirst.end();

                    for (char c : betaFirst) {
                        if (c != 'e' && follow[cur].insert(c).second) {
                            changed = true;
                        }
                    }

                    if (epsilonInBeta || i + 1 >= rhs.length()) {
                        for (char c : follow[lhs]) {
                            if (follow[cur].insert(c).second) {
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "\n--- RESULTS ---\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (char c : first[nt]) cout << c << " ";
        cout << "}\t";
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : follow[nt]) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}