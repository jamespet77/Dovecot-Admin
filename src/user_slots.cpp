/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-05-05 08:56:23 -0500 (Mon, 05 May 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <mainwindowimpl.h>

void	MainWindowImpl::UcheckValidate() {
	if (txt_userUserName->text() != "" && txt_userPasswd->text() != "") {
		btn_userUpdate->setEnabled(true);
		btn_userAdd->setEnabled(true);
	} else {
		btn_userUpdate->setEnabled(false);
		btn_userAdd->setEnabled(false);
	}
}

void	MainWindowImpl::addUser() {
	USER *node;
	DOMAIN *dm;
	node = new USER;
	char tmpHD[128];
	node->setUserName(txt_userUserName->text().toLatin1().data());
	node->setRealName(txt_userRealName->text().toLatin1().data());
	node->setPasswd(txt_userPasswd->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		sprintf(tmpHD,"%s/%s/%s",ROOT_DIR,dm->getName(),node->getUserName());
		node->setHomeDir(tmpHD);
		if (user_create(node,dm->getName(),dm->getPWfile())) {
			user_update_forward(txt_userForwardInfo->toPlainText().toLatin1().data(),node,dm->getName());
			user_update_whitelist(txt_userWhitelist->toPlainText().toLatin1().data(),node,dm->getName());
			log("User Created Successfully\n");
		} else {
			log("Error in User Dir creation:\n");
		}
	}
	user_list_create(dm->getName(),dm->getPWfile());
	load_user_list(list_users);
}

void	MainWindowImpl::updateUser() {
	USER *node;
	DOMAIN *dm;
	node = new USER;
	node->setUserName(txt_userUserName->text().toLatin1().data());
	node->setRealName(txt_userRealName->text().toLatin1().data());
	node->setPasswd(txt_userPasswd->text().toLatin1().data());
	node->setHomeDir(txt_userHomeDir->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		if (user_remove(node,dm->getName(),dm->getPWfile())) {
			log("User removed Successfully\n");
		} else {
			log("Error in User Dir deletion:\n");
		}
	}
	addUser();
}

void	MainWindowImpl::removeUser() {
	USER *node;
	DOMAIN *dm;
	node = new USER;
	node->setUserName(txt_userUserName->text().toLatin1().data());
	node->setRealName(txt_userRealName->text().toLatin1().data());
	node->setPasswd(txt_userPasswd->text().toLatin1().data());
	node->setHomeDir(txt_userHomeDir->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		if (user_remove(node,dm->getName(),dm->getPWfile())) {
			log("User removed Successfully\n");
		} else {
			log("Error in User Dir deletion:\n");
		}
	}
	user_list_create(dm->getName(),dm->getPWfile());
	load_user_list(list_users);
}

void	MainWindowImpl::clearUserTab() {
	list_users->setCurrentRow(0);
	txt_userUserName->clear();
	txt_userRealName->clear();
	txt_userPasswd->clear();
	txt_userHomeDir->clear();
	txt_userForwardInfo->clear();
	txt_userWhitelist->clear();
}

void	MainWindowImpl::load_user_forward(QTextEdit *txt, USER *user) {
	char info[4096];

	user_get_forward(info,user,list_domains->currentItem()->text().toLatin1().data());
	txt->setText(info);
}

void	MainWindowImpl::load_user_whitelist(QTextEdit *txt, USER* user) {
	char info[4096];

	user_get_whitelist(info,user,list_domains->currentItem()->text().toLatin1().data());
	txt->setText(info);
}

void	MainWindowImpl::load_user_list(QListWidget *list) {
	nodeType<USER> *current;
	list->clear();
	current = user_list->firstNode();
	list->addItem("----------");
	while (current != NULL) {
		list->addItem(current->info.getUserName());
		current = current->link;	
	}
	list->sortItems();
	list->setCurrentRow(0);
}

void	MainWindowImpl::updateUserInfo() {
	USER *node;
	char fldrSize[512];
	char accessDate[512];
	node = user_list->search(list_users->currentItem()->text().toLatin1().data());
	if (cbo_topDomains->currentIndex() > 0) {
		btn_userAdd->setEnabled(true);
		btn_userUpdate->setEnabled(true);
		if(node != NULL) {
			txt_userRealName->setText(node->getRealName());
			txt_userUserName->setText(node->getUserName());
			txt_userHomeDir->setText(node->getHomeDir());
			txt_userPasswd->setText(node->getPasswd());
			folderSize(fldrSize,node->getHomeDir());
			lbl_UserDirSize->setText(fldrSize);
			fileLastAccess(accessDate,node->getHomeDir());
			lbl_UserLastAccess->setText(accessDate);
			load_user_forward(txt_userForwardInfo,node);
			load_user_whitelist(txt_userWhitelist,node);
			btn_userAdd->hide();
			btn_userUpdate->show();
			btn_userRemove->setEnabled(true);
		} else {
			txt_userRealName->clear();
			txt_userUserName->clear();
			txt_userHomeDir->clear();
			txt_userPasswd->clear();
			lbl_UserDirSize->clear();
			lbl_UserLastAccess->clear();
			txt_userForwardInfo->clear();
			txt_userWhitelist->clear();
			btn_userAdd->show();
			btn_userUpdate->hide();
			btn_userRemove->setEnabled(false);
		}
	} else {
		btn_userAdd->setEnabled(false);
		btn_userUpdate->setEnabled(false);
	}
	UcheckValidate();
}

void	MainWindowImpl::updatePasswdDisplay() {
	if (cbx_userHidePW->checkState() == Qt::Checked) {
		txt_userPasswd->setEchoMode(QLineEdit::Password);
	} else {
		txt_userPasswd->setEchoMode(QLineEdit::Normal);
	}
}
