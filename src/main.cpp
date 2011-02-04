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

#include <QApplication>
#include <QStyleFactory>
#include <QStyle>
#include "mainwindowimpl.h"
#include <globals.h>
#include <utils.h>
#include <domain.h>
#include <domain_io.h>
//#include <remote.h>
//
passwd *dc_uid;

int main(int argc, char ** argv) {
/////////////////////////////////////////
//	load_config(config);
//	/////////////////////////////////////////////////
	QApplication app( argc, argv );
	QApplication::setStyle(QStyleFactory::create("plastique"));
	MainWindowImpl win;
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	if((dc_uid = getpwnam(UID)) == NULL) {
		printf("Username Error. Please Check settings\n");
		return -1;
	} else {
		if (setgid(dc_uid->pw_gid) == 0) {
			printf("Usergroup changed to %s group\n",GID);
	} else {
			printf("Failed to change to %s group\n",GID);
		}
		if (setuid(dc_uid->pw_uid) == 0) {
			printf("Username changed to %s\n",UID);
		} else {
			printf("Failed to change to %s user\n",UID);
		}
}
return app.exec();
//	////////////////////////////////////////////////////
}
