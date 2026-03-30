%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
[0-9]+(\.[0-9]+)? {
    yylval.str = strdup(yytext);
    return NUMBER;
}

[ \t]    ;
\n       return '\n';
.        return yytext[0];
%%

int yywrap(void) {
    return 1;
}
