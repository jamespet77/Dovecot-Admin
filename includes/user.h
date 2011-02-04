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

#ifndef USER_HH
#define USER_HH

class USER {
	private:
		char realname[128];
		char username[128];
		char passwd[128];
		char home_dir[128];
	public:
		USER();
		USER(const char *rname, const char *uname, const char *pw, const char *hd);
		USER&	operator= (const USER& u);
		friend bool operator== (const USER& lhs, const USER& rhs);
		friend bool operator!= (const USER& lhs, const USER& rhs);
		friend bool operator<= (const USER& lhs, const USER& rhs);
		friend bool operator< (const USER& lhs, const USER& rhs);
		friend bool operator>= (const USER& lhs, const USER& rhs);
		friend bool operator> (const USER& lhs, const USER& rhs);
		int 	compare(const USER& lhs, const USER& rhs) const;
		const char	*getRealName() const;
		void	setRealName(const char *rname);
		const char	*getUserName() const;
		const char	*getName() const;
		void	setUserName(const char *uname);
		const char	*getPasswd() const;
		void	setPasswd(const char *pw);
		const char	*getHomeDir() const;
		void	setHomeDir(const char *hd);
};

#endif
