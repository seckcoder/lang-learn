%{
#include <stdio.h>
#include "y.tab.h"
void yyerror(char *s);

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

[ \t\n]+   ; /* ignore whitespace */

. yerror("invalid character");

%%


