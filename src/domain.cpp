/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-28 19:46:31 -0500 (Mon, 28 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include <globals.h>
#include <domain.h>

DOMAIN::DOMAIN() {
}

DOMAIN::DOMAIN(const char *n, const char *pw) {
//	printf("%s\n",n);
	sprintf(this->name,"%s",n);
	sprintf(this->passwd_file,"%s",pw);
}

DOMAIN&	DOMAIN::operator= (const DOMAIN& d) {
	if (&d == this) {
		return *this;
	} else {
		this->setName(d.name);
		this->setPWfile(d.passwd_file);
		this->setType(d.type);
		this->setData(d.data);
	}
	return *this;
}

bool operator== (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) == 0);
}

bool operator!= (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) != 0);
}

bool operator<= (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) <= 0);
}

bool operator< (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) < 0);
}

bool operator>= (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) >= 0);
}

bool operator> (const DOMAIN& lhs, const DOMAIN& rhs) {
    return (lhs.compare(lhs,rhs) > 0);
}

int DOMAIN::compare(const DOMAIN& lhs, const DOMAIN& rhs) const {
	return strcmp(lhs.getName(),rhs.getName());
}

const char	*DOMAIN::getName() const {
	return this->name;
}

void	DOMAIN::setName(const char *n) {
	sprintf(this->name,"%s",n);
}

const char	*DOMAIN::getPWfile() const {
	return this->passwd_file;
}

void	DOMAIN::setPWfile(const char *pw) {
	sprintf(this->passwd_file,"%s",pw);
}

const char	*DOMAIN::getType() const {
	return this->type;
}

void	DOMAIN::setType(const char *t) {
	sprintf(this->type,"%s",t);
}

const char	*DOMAIN::getData() const {
	return this->data;
}

void	DOMAIN::setData(const char *d) {
	sprintf(this->data,"%s",d);
}
