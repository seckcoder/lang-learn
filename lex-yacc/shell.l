%{
#include <stdio.h>
// yacc sucks. We have to include shell.h here
// even the lexer will never use anything of it.
// since in file "y.tab.h", it depends on NodeType
// definition in shell.h. But yacc doesn't include
// shell.h in y.tab.h, so we have to include it
// the firsttime we include y.tab.h...
#include "shell.h"
#include "y.tab.h"
/*void yyerror(char *);*/

%}

digit [0-9]
letter [A-Za-z]
param_tok [^|<> \t\n]

%%

0  { yylval.int_v = atoi(yytext); return INTEGER; }

[1-9][0-9]* { yylval.int_v = atoi(yytext); return INTEGER; }

({letter}|{digit})({letter}|{digit}|_)* { yylval.var = yytext; return VARIABLE;  }


[-|><] return *yytext;

{param_tok}+ { yylval.param = yytext; return PARAM; }

[ \t]+   ; /* ignore whitespace */
\n    { return END; }

%%


int yywrap(void) {
    printf("yywrap\n");
    return 1;
}
