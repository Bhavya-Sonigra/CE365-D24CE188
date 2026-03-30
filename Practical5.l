%{
#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 100
#define MAX_LEN 50

int line_number = 1;

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

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
ICONST      {DIGIT}+
SCONST      \'([^'\\\n]|\\.)\'|\"([^"\\\n]|\\.)*\"
KEYWORD     "int"|"char"|"return"|"void"|"if"|"else"
OPERATOR    "="|"+"|"-"|"*"|"/"|"=="|"<="|">="
PUNCT       "("|")"|"{"|"}"|";"|","
ERROR_ID    {DIGIT}+{LETTER}+

%option noyywrap

%%

[ \t\r]+    { /* Skip whitespace */ }
\n          { line_number++; }

"//".* { /* Skip single-line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/" { 
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
                if(strcmp(yytext, "main") != 0) add_to_symbol_table(yytext);
             }

{ERROR_ID}   { printf("\nLEXICAL ERROR\nLine %d : %s invalid lexeme\n\n", line_number, yytext); }

.            { /* Catch all other characters */ }

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./lexer <filename>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    printf("TOKENS\n");
    yyin = fp;
    yylex();

    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%d) %s\n", i + 1, symbol_table[i]);
    }

    fclose(fp);
    return 0;
}