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
    NodeType *nptr;
};

/*yylval of token: INTENGER should be bound with int_v*/
%token <int_v> INTEGER;
/*...*/
%token <var> VARIABLE;
%token '>' '<'
%left '|' '<' '>'

%type <nptr> cmd pipe redir param_list param

%%

function:
         function cmd '\n' { eval($2); freeNode($2); }
       | function redir '\n' { eval($2); freeNode($2); }
       | function pipe '\n' { eval($2); freeNode($2); }
       | /*null*/
       ;

cmd:
      VARIABLE { $$ = create_cmd($1, NULL); }
    | VARIABLE param_list { $$ = create_cmd($1, $2); }
    ; 

redir:
      cmd '>' param { $$ = create_redir($1, $3); }
    | param '<' cmd { $$ = create_redir($3, $1); }

param:
      VARIABLE { $$ = create_param(0, $1); }
    | '-' VARIABLE { $$ = create_param(1, $2); }
    ;

pipe: pipe '|' cmd { $$ = create_pipe($3, $1); }
    | cmd { $$ = create_pipe($1, NULL); }
    ; 

param_list:
          param_list param { $$ = create_pair($2, $1); }
        | param { $$ = create_pair($1, NULL); }
        ;
%%


void yyerror(char *s) {
    fprintf(stderr, "%s", s);
}

int main(void) {
    yyparse();
    return 0;
}
