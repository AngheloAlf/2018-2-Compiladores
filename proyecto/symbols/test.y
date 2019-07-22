/**
 * @file  test.y
 * @brief Parser for symbol table test
 */

%{
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "symbol.h"

int yylex(void);

void yyerror(const char *fmt, ...)
	__attribute__((format (printf, 1, 2)));

%}

%union {
	const char *name;
}

%token ENTER LEAVE DUMP DEFINE LOOKUP
%token <name>IDENT

%%
tests: tests test
     | /* Empty */
     ;

test: '\n' /* Blank line... */
    | ENTER '\n' { enter_scope(); }
    | LEAVE '\n' { leave_scope(); }
    | DUMP  '\n' { dump_symtab(); }
    | DEFINE IDENT '\n'
                 {
		    struct symbol *p = add($2);
		    if(p)
			    printf("%s added\n", $2);
		    else
			    printf("%s duplicate\n", $2);
                 }
    | LOOKUP IDENT '\n'
                 {
                   struct symbol *p = lookup($2);
		   if(p)
		       dump_symbol(p);
		   else
			   printf("%s not found\n", $2);
		   free((void *) $2);
                 }
    | error '\n' { yyerrok; }
    ;
%%
void yyerror(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}
