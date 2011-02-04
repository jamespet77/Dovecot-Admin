/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-30 09:14:55 -0500 (Wed, 30 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef ALIAS_HH
#define ALIAS_HH

class ALIAS {
	private:
		char aliasname[128];
	public:
		ALIAS();
		ALIAS(const char *uname);
		ALIAS&	operator= (const ALIAS& u);
		friend bool operator== (const ALIAS& lhs, const ALIAS& rhs);
        friend bool operator!= (const ALIAS& lhs, const ALIAS& rhs);
        friend bool operator<= (const ALIAS& lhs, const ALIAS& rhs);
        friend bool operator< (const ALIAS& lhs, const ALIAS& rhs);
        friend bool operator>= (const ALIAS& lhs, const ALIAS& rhs);
        friend bool operator> (const ALIAS& lhs, const ALIAS& rhs);
        int     compare(const ALIAS& lhs, const ALIAS& rhs) const;
		const char	*getAliasName() const;
		const char	*getName() const;
		void	setAliasName(const char *uname);
};

#endif
