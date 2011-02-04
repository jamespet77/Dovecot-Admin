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

#include "mainwindowimpl.h"
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	domain_list_create();
	load_domain_list(cbo_topDomains);
	load_domain_list(list_domains);

	txt_domainAlias->hide();
	lbl_alias->hide();
	txt_userPasswd->setEchoMode(QLineEdit::Password);

	connect( tab_mainWidget, SIGNAL(currentChanged(int)),this, SLOT(tabSwitch()) );
	//connect( pushButton, SIGNAL(clicked()),this, SLOT(fillLabel()) );
	//DOMAIN
	connect( btn_domainClear, SIGNAL(clicked()),this, SLOT(clearDomainTab()) );
	connect( btn_domainAdd, SIGNAL(clicked()),this, SLOT(addDomain()) );
	connect( btn_domainUpdate, SIGNAL(clicked()),this, SLOT(updateDomain()) );
	connect( btn_domainRemove, SIGNAL(clicked()),this, SLOT(removeDomain()) );
	connect( list_domains, SIGNAL(itemSelectionChanged()),this, SLOT(updateDomainSelection2()) );
	connect( cbo_topDomains, SIGNAL(currentIndexChanged(int)),this, SLOT(updateDomainSelection1()) );
	connect( cbx_createDomainAlias, SIGNAL(stateChanged(int)),this, SLOT(displayAliasTools()) );
	//USER
	connect( txt_userUserName, SIGNAL(textChanged (const QString&)),this, SLOT(UcheckValidate()) );
	connect( txt_userPasswd, SIGNAL(textChanged (const QString&)),this, SLOT(UcheckValidate()) );

	connect( btn_userClear, SIGNAL(clicked()),this, SLOT(clearUserTab()) );
	connect( btn_userAdd, SIGNAL(clicked()),this, SLOT(addUser()) );
	connect( btn_userUpdate, SIGNAL(clicked()),this, SLOT(updateUser()) );
	connect( btn_userRemove, SIGNAL(clicked()),this, SLOT(removeUser()) );
	connect( list_users, SIGNAL(itemSelectionChanged()),this, SLOT(updateUserInfo()) );
	connect( cbx_userHidePW, SIGNAL(stateChanged(int)),this, SLOT(updatePasswdDisplay()) );
	
	//ALIAS
	connect( txt_aliasUserName, SIGNAL(textChanged (const QString&)),this, SLOT(AcheckValidate()) );

	connect( btn_aliasClear, SIGNAL(clicked()),this, SLOT(clearAliasTab()) );
	connect( btn_aliasAdd, SIGNAL(clicked()),this, SLOT(addAlias()) );
	connect( btn_aliasUpdate, SIGNAL(clicked()),this, SLOT(updateAlias()) );
	connect( btn_aliasRemove, SIGNAL(clicked()),this, SLOT(removeAlias()) );
	connect( list_alias, SIGNAL(itemSelectionChanged()),this, SLOT(updateAliasInfo()) );

}

void	MainWindowImpl::load_domain_list(QComboBox *list) {
	nodeType<DOMAIN> *current;
	list->clear();
	current = domain_list->firstNode();
	list->addItem("----------");
	while (current != NULL) {
		list->addItem(current->info.getName());
		current = current->link;	
	}
}

void	MainWindowImpl::tabSwitch() {
	switch(tab_mainWidget->currentIndex()) {
		case 0: //DOMAINS
//			LOGGING = false;
			break;
		case 1: //USERS
//			LOGGING = false;
			if (list_domains->currentRow() > 0) {
				load_user_list(list_users);
			}
			break;
		case 2: //ALIASES
//			LOGGING = false;
			if (list_domains->currentRow() > 0) {
				load_alias_list(list_alias);
			}
			break;
//		case 3: //LOGS
//			LOGGING = true;
//				startLogUpdate(logfile,txt_logWatch);
//			break;
		default:
			break;
	}
}
