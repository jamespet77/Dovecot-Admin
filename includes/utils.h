/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-01-14 14:20:22 -0600 (Mon, 14 Jan 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/


#ifndef UTILS_HH
#define UTILS_HH

#include <stdio.h>
#include <ext/stdio_filebuf.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <globals.h>
#include <map>

using namespace std;

void    sys_cmd(const char *input, char *buffer);
void    system_cmd(char *buffer, const char *input, ...);
char    *lowercase(char *str);
char    *uppercase(char *str);

bool	file_exists(const char *file);
void    load_config(map<char *,char *> &conf);
void	clean(char *str);
void	cleanNewLine(char *str);
void	split(const char *input,char *str1, char *str2, const char delim = '=');
void	folderSize(char *buffer, const char *file);
void	fileLastAccess(char *buf, const char *file);
//void 	sleep( clock_t wait );
#endif
