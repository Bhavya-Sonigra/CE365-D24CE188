#include <iostream>
#include <string>
using namespace std;

int main() {
    int symbols;
    cout << "Number of input symbols : ";
    cin >> symbols;

    char inputSymbols[10];
    cout << "Input symbols : ";
    for (int i = 0; i < symbols; i++) {
        cin >> inputSymbols[i];
    }

    int states;
    cout << "Enter number of states : ";
    cin >> states;

    int startState;
    cout << "Initial state : ";
    cin >> startState;

    int acceptCount;
    cout << "Number of accepting states : ";
    cin >> acceptCount;

    int acceptStates[10];
    cout << "Accepting states : ";
    for (int i = 0; i < acceptCount; i++) {
        cin >> acceptStates[i];
    }

    int transition[20][20];
    cout << "Transition table :" << endl;

    for (int i = 1; i <= states; i++) {
        for (int j = 0; j < symbols; j++) {
            int nextState;
            cout << i << " to " << inputSymbols[j] << " -> ";
            cin >> nextState;
            transition[i][j] = nextState;
        }
    }

    string input;
    cout << "Input string : ";
    cin >> input;

    int currentState = startState;

    for (int i = 0; i < input.length(); i++) {
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