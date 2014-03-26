%{
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
void yyerror(char *s);
int yylex(void);
%}

%union {
    int int_v;
    char* var;
    char* param;
    NodeType *nptr;
};

/*yylval of token: INTENGER should be bound with int_v*/
%token <int_v> INTEGER;
/*...*/
%token <var> VARIABLE;
%token <param> PARAM;
%token '>' '<'
%left '|' '<' '>'

%type <nptr> cmd pipe param_list

%%

program:
       cmd { eval($1); freeNode($1); }
       ;

cmd:
     VARIABLE { $$ = create_cmd($1, NULL); }
    | VARIABLE param_list { $$ = create_cmd($1, $2); }
    | pipe { $$ = $1; }
    | cmd '>' PARAM { $$ = create_redir($1, $3); }
    | PARAM '<' cmd { $$ = create_redir($3, $1); }
    ;

pipe:
      pipe '|' cmd { $$ = create_pipe($3, $1); }
    | cmd { $$ = create_pipe($1, NULL); }
    ;

param_list:
          param_list PARAM { $$ = create_pair($2, $1); }
        | PARAM { $$ = create_pair($1, NULL); }
        ;
%%


void yyerror(char *s) {
    fprintf(stderr, "%s", s);
}

int main(void) {
    yyparse();
    return 0;
}
