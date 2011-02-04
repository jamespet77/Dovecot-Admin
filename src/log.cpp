/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-28 22:35:54 -0500 (Mon, 28 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include <log.h>

void	log(const char *msg, ...) {
	FILE *fh;
	char file[256];
	va_list fmtargs;
	char buffer[1024];

	va_start(fmtargs,msg);
	vsnprintf(buffer,sizeof(buffer) - 1,msg,fmtargs);
	va_end(fmtargs);
	sprintf(file,"%s/%s",LOG_DIR,LOG_FILE);

	fh = fopen(file,"a");
	if (fh != NULL) {
		fputs(buffer,fh);
		fclose(fh);
	}
}
