/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-23 12:07:31 -0500 (Wed, 23 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef DOMAIN_IO_HH
#define DOMAIN_IO_HH

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <globals.h>
#include <utils.h>
#include <log.h>

bool	domain_create(const char *name);
bool	domain_update(const char *oldname, const char *name);
bool	domain_remove(const char *name);
bool	domain_create_alias(const char *orig, const char *alias);

void	domain_typedata(DOMAIN *node, const char *info);
void	domain_list_create();

#endif
