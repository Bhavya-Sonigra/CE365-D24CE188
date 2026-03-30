%{
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 256

char str[MAX_INPUT_LEN];
int i = 0;
int invalid_input = 0;
int parse_error = 0;

void S();
void A();
void B();
void C();

void error() {
    parse_error = 1;
}

void append_token(const char *text) {
    size_t current_len = strlen(str);
    size_t token_len = strlen(text);

    if (current_len + token_len >= MAX_INPUT_LEN) {
        invalid_input = 1;
        return;
    }

    memcpy(str + current_len, text, token_len + 1);
}

void reset_state() {
    str[0] = '\0';
    i = 0;
    invalid_input = 0;
    parse_error = 0;
}

void A() {
    if (parse_error)
        return;

    if (str[i] == 'a')
        i++;
}

void B() {
    if (parse_error)
        return;

    if (str[i] == 'b')
        i++;
}

void C() {
    if (parse_error)
        return;

    if (str[i] == 'c') {
        i++;
    } else if (str[i] == '(') {
        i++;
        S();
        if (str[i] == ')')
            i++;
        else
            error();
    } else {
        error();
    }
}

void S() {
    if (parse_error)
        return;

    A();
    B();
    C();
}
%}

%%
[abc()]+   { append_token(yytext); }
[ \t\r]+   { /* Ignore whitespace inside the input */ }
.          { invalid_input = 1; }
\n         {
               printf("\nPredictive Parsing Table:\n");
               printf("---------------------------------\n");
               printf("Non-Terminal | a | b | c | ( | ) | $\n");
               printf("---------------------------------\n");
               printf("S            | ABC | ABC | ABC | ABC | - | -\n");
               printf("A            | a   | e   | e   | e   | - | -\n");
               printf("B            | -   | b   | e   | e   | - | -\n");
               printf("C            | -   | -   | c   | (S) | - | -\n");

               printf("\nGrammar is LL(1)\n");

               i = 0;
               parse_error = 0;
               if (!invalid_input && str[0] != '\0')
                   S();

               if (!invalid_input && !parse_error && str[i] == '\0')
                   printf("Valid string\n");
               else
                   printf("Invalid string\n");

               reset_state();
           }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter string: ");
    yylex();
    return 0;
}
