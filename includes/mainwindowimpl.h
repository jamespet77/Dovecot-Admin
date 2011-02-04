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


#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include <globals.h>
#include "ui_mainwindow.h"
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private:
	void	load_domain_list(QComboBox *list);
	void	load_domain_list(QListWidget *list);
	//USER functions
	void	load_user_list(QListWidget *list);
	void	load_user_whitelist(QTextEdit *txt, USER *user);
	void	load_user_forward(QTextEdit *txt, USER *user);
	void    startLogUpdate(const char *lock, QTextEdit *txt);
	//ALIAS functions
	void	load_alias_list(QListWidget *list);
	void	load_alias_whitelist(QTextEdit *txt, ALIAS *user);
	void	load_alias_forward(QTextEdit *txt, ALIAS *user);
private slots:
	void	tabSwitch();
//DOMAIN SLOTS
	void	addDomain();
	void	updateDomain();
	void	removeDomain();
	void	updateDomainSelection1();
	void	updateDomainSelection2();
	void	clearDomainTab();
	void	displayAliasTools();
//USER SLOTS
	void	UcheckValidate();
	void	addUser();
	void	updateUser();
	void	removeUser();
	void	updateUserInfo();
	void	clearUserTab();
	void	updatePasswdDisplay();
//ALIAS SLOTS
	void	AcheckValidate();
	void	addAlias();
	void	updateAlias();
	void	removeAlias();
	void	updateAliasInfo();
	void	clearAliasTab();
//LOG SLOTS
};
#endif

