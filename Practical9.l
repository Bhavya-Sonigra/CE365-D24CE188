%{
#include "y.tab.h"
%}

%%
i          { return 'i'; }
t          { return 't'; }
e          { return 'e'; }
a          { return 'a'; }
b          { return 'b'; }
[ \t\r]+   { /* Ignore whitespace */ }
\n         { return '\n'; }
.          { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
