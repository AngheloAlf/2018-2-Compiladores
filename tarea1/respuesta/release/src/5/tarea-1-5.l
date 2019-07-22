%option nounput yylineno
%option batch
LETRA [a-zA-Z]
DEMAS [0-9]|"-"

%%

({DEMAS}|{LETRA})*{LETRA}+({DEMAS}|{LETRA})*    return 1;
\n  ;
.   ;

%%

int yywrap(){
    return 1;
}
