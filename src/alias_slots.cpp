/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-29 15:03:48 -0500 (Tue, 29 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <mainwindowimpl.h>

void	MainWindowImpl::AcheckValidate() {
	if (txt_aliasUserName->text() != "") {
		btn_aliasUpdate->setEnabled(true);
		btn_aliasAdd->setEnabled(true);
	} else {
		btn_aliasUpdate->setEnabled(false);
		btn_aliasAdd->setEnabled(false);
	}
}

void	MainWindowImpl::addAlias() {
	ALIAS *node;
	DOMAIN *dm;
	node = new ALIAS;
	node->setAliasName(txt_aliasUserName->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		if (alias_create(node,dm->getName())) {
			alias_update_forward(txt_aliasForwardInfo->toPlainText().toLatin1().data(),node,dm->getName());
			alias_update_whitelist(txt_aliasWhitelist->toPlainText().toLatin1().data(),node,dm->getName());
			log("Alias Created Successfully\n");
		} else {
			log("Error in Alias Dir creation:\n");
		}
	}
	alias_list_create(dm->getName());
	load_alias_list(list_alias);
}

void	MainWindowImpl::updateAlias() {
	ALIAS *node;
	DOMAIN *dm;
	node = new ALIAS;
	node->setAliasName(txt_aliasUserName->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		if (alias_remove(node,dm->getName())) {
			log("Alias removed Successfully\n");
		} else {
			log("Error in Alias Dir deletion:\n");
		}
	}
	addAlias();
}

void	MainWindowImpl::removeAlias() {
	ALIAS *node;
	DOMAIN *dm;
	node = new ALIAS;
	node->setAliasName(txt_aliasUserName->text().toLatin1().data());
	dm = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
	if (dm != NULL) {
		if (alias_remove(node,dm->getName())) {
			log("Alias removed Successfully\n");
		} else {
			log("Error in Alias Dir deletion:\n");
		}
	}
	alias_list_create(dm->getName());
	load_alias_list(list_alias);
}

void	MainWindowImpl::clearAliasTab() {
	list_alias->setCurrentRow(0);
	txt_aliasUserName->clear();
	txt_aliasForwardInfo->clear();
	txt_aliasWhitelist->clear();
}

void	MainWindowImpl::load_alias_forward(QTextEdit *txt, ALIAS *alias) {
	char info[4096];

	alias_get_forward(info,alias,list_domains->currentItem()->text().toLatin1().data());
	txt->setText(info);
}

void	MainWindowImpl::load_alias_whitelist(QTextEdit *txt, ALIAS* alias) {
	char info[4096];

	alias_get_whitelist(info,alias,list_domains->currentItem()->text().toLatin1().data());
	txt->setText(info);
}

void	MainWindowImpl::load_alias_list(QListWidget *list) {
	nodeType<ALIAS> *current;
	list->clear();
	current = alias_list->firstNode();
	list->addItem("----------");
	while (current != NULL) {
		list->addItem(current->info.getAliasName());
		current = current->link;	
	}
	list->sortItems();
	list->setCurrentRow(0);
}

void	MainWindowImpl::updateAliasInfo() {
	ALIAS *node;
	node = alias_list->search(list_alias->currentItem()->text().toLatin1().data());
	if (cbo_topDomains->currentIndex() > 0) {
		btn_aliasAdd->setEnabled(true);
		btn_aliasUpdate->setEnabled(true);
		if(node != NULL) {
			txt_aliasUserName->setText(node->getAliasName());
			load_alias_forward(txt_aliasForwardInfo,node);
			load_alias_whitelist(txt_aliasWhitelist,node);
			btn_aliasAdd->hide();
			btn_aliasUpdate->show();
			btn_aliasRemove->setEnabled(true);
		} else {
			txt_aliasUserName->clear();
			txt_aliasForwardInfo->clear();
			txt_aliasWhitelist->clear();
			btn_aliasAdd->show();
			btn_aliasUpdate->hide();
			btn_aliasRemove->setEnabled(false);
		}
	} else {
		btn_aliasAdd->setEnabled(false);
		btn_aliasUpdate->setEnabled(false);
	}
	AcheckValidate();
}
