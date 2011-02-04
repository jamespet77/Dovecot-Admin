%{
/*
DoveCot Admin
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-01-14 16:35:48 -0600 (Mon, 14 Jan 2008) $
$Rev: 477 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include <stdio.h>
#include <iostream>
#define YYDEBUG 1       ///Debugging stuff

using namespace std;
/// Wrapper for yyFlexLexer yylex function
int yylex(/** VOID */);

///Output for error production
void yyerror(const char *s);

///input stream
extern ifstream *yyin;

%}

%error-verbose

%start program

%token	ID
%token	ADD
%token	DEL
%token	LIST
%token	CHANGE
%token	USER
%token	ALIAS
%token	DOMAIN
%token	EMAIL
%token	WL
%token	TO
%token	FROM
%token	FOR
%token	PASSWD
%token	EXIT
%token	HELP

%%

program:
	   		command assignment {
			}
		|	EXIT {
			}
		|	HELP {
				cout << "Load help file here...  Not Yet Implemented." << endl;
			}
		|
		;

command:
			ADD {
			} type parameter_list
		|	DEL {
			} type parameter_list
		|	CHANGE {
			} PASSWD parameter
		|	LIST {
			} type parameter_list
		;

assignment:
		  	TO {
			}	type parameter
		|	FROM {
			}	type parameter
		|	FOR {
			}	type parameter
		|
		;

type:
			USER {
			}
		|	ALIAS {
			}
		|	DOMAIN {
			}
		|	EMAIL {
			}
		;

parameter_list:
			parameter
		|	parameter_list ',' parameter
		;

parameter:
		 	ID
		|
		;

%%

///Wrapper for FlexLexer class yylex 
int yylex() {
    return 1;
}

void yyerror(char const *s) {
    cerr << s << endl;
}
