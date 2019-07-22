/**
 * @file  test.l
 * @brief Scanner for symbol table test
 */

%option noyywrap nounput noinput

%{
#include <string.h>
#include <stdlib.h>

#include "y.tab.h"
%}


ident	[a-zA-Z_][a-zA-Z_0-9]*
%%
[ \t]   ;
"\n"    return yytext[0];

enter	return ENTER;
leave   return LEAVE;
dump    return DUMP;
define  return DEFINE;
lookup  return LOOKUP;

{ident} {
	  yylval.name = strdup(yytext);
          return IDENT;
        }
