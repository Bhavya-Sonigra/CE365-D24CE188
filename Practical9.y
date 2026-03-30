%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%%

S  : 'i' E 't' S S1
   | 'a'
   ;

S1 : 'e' S
   | /* empty */
   ;

E  : 'b'
   ;

%%

void yyerror(const char *s) {
    (void)s;
    printf("Invalid string\n");
    exit(1);
}

int main(void) {
    printf("Enter string: ");
    if (yyparse() == 0) {
        printf("Valid string\n");
    }
    return 0;
}
