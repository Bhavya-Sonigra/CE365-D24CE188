%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyparse(void);
void yyerror(const char *s);
%}

%token I B T E A

%%

S : M
  | U
  ;

M : I C T M E M
  | A
  ;

U : I C T S
  | I C T M E U
  ;

C : B ;

%%

void yyerror(const char *s) {
  (void)s;
    printf("Invalid string\n");
    exit(0);
}

int main() {
    printf("Enter string: ");
    yyparse();
    printf("Valid string\n");
    return 0;
}