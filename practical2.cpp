#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int symbols;
    cout << "Number of input symbols : ";
    cin >> symbols;

    if (symbols <= 0) {
        cout << "Invalid automaton";
        return 0;
    }

    vector<char> inputSymbols(symbols);
    cout << "Input symbols : ";
    for (int i = 0; i < symbols; i++) {
        cin >> inputSymbols[i];
    }

    int states;
    cout << "Enter number of states : ";
    cin >> states;

    if (states <= 0) {
        cout << "Invalid automaton";
        return 0;
    }

    int startState;
    cout << "Initial state : ";
    cin >> startState;

    if (startState < 1 || startState > states) {
        cout << "Invalid automaton";
        return 0;
    }

    int acceptCount;
    cout << "Number of accepting states : ";
    cin >> acceptCount;

    if (acceptCount < 0) {
        cout << "Invalid automaton";
        return 0;
    }

    vector<int> acceptStates(acceptCount);
    cout << "Accepting states : ";
    for (int i = 0; i < acceptCount; i++) {
        cin >> acceptStates[i];
        if (acceptStates[i] < 1 || acceptStates[i] > states) {
            cout << "Invalid automaton";
            return 0;
        }
    }

    vector<vector<int>> transition(states + 1, vector<int>(symbols, -1));
    cout << "Transition table :" << endl;

    for (int i = 1; i <= states; i++) {
        for (int j = 0; j < symbols; j++) {
            int nextState;
            cout << i << " to " << inputSymbols[j] << " -> ";
            cin >> nextState;
            if (nextState < 1 || nextState > states) {
                cout << "Invalid automaton";
                return 0;
            }
            transition[i][j] = nextState;
        }
    }

    string input;
    cout << "Input string : ";
    cin >> input;

    int currentState = startState;

    for (size_t i = 0; i < input.length(); i++) {
        char ch = input[i];
        int found = 0;

        for (int j = 0; j < symbols; j++) {
            if (ch == inputSymbols[j]) {
                currentState = transition[currentState][j];
                found = 1;
                break;
            }
        }

        if (!found) {
            cout << "\nInvalid String";
            return 0;
        }
    }

    for (int i = 0; i < acceptCount; i++) {
        if (currentState == acceptStates[i]) {
            cout << "\nValid String";
            return 0;
        }
    }

    cout << "\nInvalid String";
    return 0;
}