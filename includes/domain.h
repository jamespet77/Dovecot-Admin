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

#ifndef DOMAIN_HH
#define DOMAIN_HH

class DOMAIN {
	private:
		char name[128];
		char passwd_file[128];
		char type[8];
		char data[128];
	public:
		DOMAIN();
		DOMAIN(const char *n, const char *pw);
		DOMAIN&	operator= (const DOMAIN& d);
		friend bool operator== (const DOMAIN& lhs, const DOMAIN& rhs);
		friend bool operator!= (const DOMAIN& lhs, const DOMAIN& rhs);
		friend bool operator<= (const DOMAIN& lhs, const DOMAIN& rhs);
		friend bool operator< (const DOMAIN& lhs, const DOMAIN& rhs);
		friend bool operator>= (const DOMAIN& lhs, const DOMAIN& rhs);
		friend bool operator> (const DOMAIN& lhs, const DOMAIN& rhs);
		int 	compare(const DOMAIN& lhs, const DOMAIN& rhs) const;
		const char 	*getName() const ;
		void	setName(const char *n);
		const char	*getPWfile() const;
		void	setPWfile(const char *pw);
		const char	*getType() const;
		void	setType(const char *t);
		const char	*getData() const;
		void	setData(const char *d);
};

#endif
