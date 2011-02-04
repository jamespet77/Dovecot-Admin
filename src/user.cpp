/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-29 12:22:25 -0500 (Tue, 29 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include <globals.h>
#include <user.h>

USER::USER() {
	this->setRealName("");
	this->setUserName("");
	this->setPasswd("");
	this->setHomeDir("");
}

USER::USER(const char *rname, const char *uname, const char *pw, const char *hd) {
	setRealName(rname);
	setUserName(uname);
	setPasswd(pw);
	setHomeDir(hd);
}

USER&	USER::operator= (const USER& u) {
	if (&u == this) {
		return *this;
	} else {
		this->setRealName(u.realname);
		this->setUserName(u.username);
		this->setPasswd(u.passwd);
		this->setHomeDir(u.home_dir);
	}
	return *this;
}

bool operator== (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) == 0);
}

bool operator!= (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) != 0);
}

bool operator<= (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) <= 0);
}

bool operator< (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) < 0);
}

bool operator>= (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) >= 0);
}

bool operator> (const USER& lhs, const USER& rhs) {
    return (lhs.compare(lhs,rhs) > 0);
}

int USER::compare(const USER& lhs, const USER& rhs) const {
	return strcmp(lhs.getUserName(),rhs.getUserName());
}

const char	*USER::getRealName() const {
	return this->realname;
}

void	USER::setRealName(const char *rname) {
	sprintf(this->realname,"%s",rname);
}

const char	*USER::getUserName() const {
	return this->username;
}

const char	*USER::getName() const {
	return this->username;
}

void	USER::setUserName(const char *uname) {
	sprintf(this->username,"%s",uname);
}

const char	*USER::getPasswd() const {
	return this->passwd;
}

void	USER::setPasswd(const char *pw) {
	sprintf(this->passwd,"%s",pw);
}

const char	*USER::getHomeDir() const {
	return this->home_dir;
}

void	USER::setHomeDir(const char *hd) {
	sprintf(this->home_dir,"%s",hd);
}

