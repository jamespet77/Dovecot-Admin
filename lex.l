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
#define FFLEX
//#include <global.h>
#include "parser_yacc.h"

using namespace std;

%}

ID  [a-z][a-z0-9\-\.\@\_]*

%option c++
%option noyywrap
%option caseless

%%

"{"([\r\n]|([^}]|[\r\n]))*"}"	/*ignore */

[\t ]+							/*ignore */

add				return	ADD;
del				return	DEL;
delete			return 	DEL;
list			return	LIST;
change			return	CHANGE;
user			return	USER;
users			return	USER;
alias			return	ALIAS;
domain			return	DOMAIN;
domains			return	DOMAIN;
email			return	EMAIL;
wl				return	WL;
whitelist		return	WL;
pw				return	PASSWD;
pass			return	PASSWD;
passwd			return	PASSWD;
password		return	PASSWD;
to				return	TO;
from			return	FROM;
for				return	FOR;
exit			return	EXIT;
done			return	EXIT;
quit			return	EXIT;
help			return	HELP;
":"|";"|","|")"|"("|"."         return *yytext;

{ID} {
	return ID;
}

.       cerr << "Found " << yytext << " Was it expected?" << endl;

%%
