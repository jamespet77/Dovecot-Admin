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

#ifndef USER_IO_HH
#define USER_IO_HH

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <globals.h>
#include <utils.h>
#include <user.h>
#include <log.h>

bool	user_create(USER *user, const char *domain, const char *pwfile);
bool	user_remove(USER *user, const char *domain, const char *pwfile);
//bool	user_update_name(USER *olduser, const char *user, const char *domain, const char *pwfile);
bool	user_create_pw(USER *user, const char *domain, const char *pwfile);
bool	user_remove_pw(USER *user, const char *domain, const char *pwfile);
bool	user_update_pw(USER *user, const char *domain, const char *pwfile);
void	user_get_forward(char *file, USER *user, const char *domain);
bool	user_create_forward(USER *user, const char *domain);
bool	user_update_forward(const char *file, USER *user, const char *domain);
void	user_get_whitelist(char *file, USER *user, const char *domain);
bool	user_create_whitelist(USER *user, const char *domain);
bool	user_update_whitelist(const char *file, USER *user, const char *domain);

bool	user_exists(const char *user, const char *domain, const char *pwfile);
bool	create_passwd(char *outfile, const char *infile);
void	user_list_create(const char *domain, const char *pwfile);

#endif
