%{
#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_LEN 50

int line_number = 1;

// Simple structure to mock a Symbol Table
char symbol_table[MAX_SYMBOLS][MAX_LEN];
int symbol_count = 0;

void add_to_symbol_table(const char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], name) == 0) {
            return;
        }
    }
    if (symbol_count < MAX_SYMBOLS) {
        snprintf(symbol_table[symbol_count], MAX_LEN, "%s", name);
        symbol_count++;
    }
}
%}

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
ICONST      {DIGIT}+
SCONST      \'([^'\\\n]|\\.)\'|\"([^"\\\n]|\\.)*\"
KEYWORD     "int"|"char"|"return"|"if"|"else"|"while"|"for"|"void"|"float"
OPERATOR    "+"|"-"|"*"|"/"|"="|"<"|">"|"!"|"&"|"|"
PUNCT       "("|")"|"{"|"}"|"["|"]"|";"|","
WHITESPACE  [ \t\r]+
ERROR_ID    {DIGIT}+{LETTER}+

%%
\n          { line_number++; }
{WHITESPACE} { /* Skip whitespace */ }

"//".* { /* Skip single line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/" { 
                // Handle multi-line comment line counting
                for (int i = 0; yytext[i]; i++) {
                    if (yytext[i] == '\n') {
                        line_number++;
                    }
                }
            }

{KEYWORD}    { printf("Keyword: %s\n", yytext); }
{PUNCT}      { printf("Punctuation: %s\n", yytext); }
{OPERATOR}   { printf("Operator: %s\n", yytext); }
{ICONST}     { printf("Constant: %s\n", yytext); }
{SCONST}     { printf("Constant: %s\n", yytext); }

{ID}         { 
                printf("Identifier: %s\n", yytext); 
                add_to_symbol_table(yytext);
             }

{ERROR_ID}   { printf("\nLEXICAL ERROR\nLine %d : %s invalid lexeme\n\n", line_number, yytext); }

.            { /* Catch-all for any other single character errors */ }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    // To read from a file, you can use: yyin = fopen("input.c", "r");
    yylex();

    printf("\nSYMBOL TABLE ENTRIES\n");
    int printed = 0;
    for (int i = 0; i < symbol_count; i++) {
        // Excluding 'main' from symbol table if you only want variables
        if (strcmp(symbol_table[i], "main") != 0) {
            printed++;
            printf("%d) %s\n", printed, symbol_table[i]);
        }
    }
    return 0;
}