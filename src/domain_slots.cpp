/*
DCA
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-04-29 17:13:50 -0500 (Tue, 29 Apr 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "mainwindowimpl.h"

void	MainWindowImpl::load_domain_list(QListWidget *list) {
	nodeType<DOMAIN> *current;
	list->clear();
	current = domain_list->firstNode();
	list->addItem("----------");
	while (current != NULL) {
		list->addItem(current->info.getName());
		current = current->link;	
	}
}

void	MainWindowImpl::addDomain() {
	if (txt_domainName->text() != "" && txt_domainAlias->text() != "") {
		if (domain_create_alias(txt_domainAlias->text().toLatin1().data(), txt_domainName->text().toLatin1().data())) {
			domain_list_create();
			load_domain_list(list_domains);
			load_domain_list(cbo_topDomains);
			clearDomainTab();
		} else {
			log("ERROR - in domain alias creation.\n");
		}
	} else {
		if (domain_create(txt_domainName->text().toLatin1().data())) {
			domain_list_create();
			load_domain_list(list_domains);
			load_domain_list(cbo_topDomains);
			clearDomainTab();	
		} else {
			log("ERROR - in domain creation.\n");
		}
	}
}

void	MainWindowImpl::updateDomain() {
	if (domain_update(list_domains->currentItem()->text().toLatin1().data(),txt_domainName->text().toLatin1().data())) {
		domain_list_create();
		load_domain_list(list_domains);
		load_domain_list(cbo_topDomains);
		clearDomainTab();
	} else {
		log("ERROR - in domain update.\n");
	}
}

void	MainWindowImpl::removeDomain() {
	if (domain_remove(txt_domainName->text().toLatin1().data())) {
		domain_list_create();
		load_domain_list(list_domains);
		load_domain_list(cbo_topDomains);
		clearDomainTab();
	} else {
		log("ERROR - in domain removal.\n");
	}
}

void	MainWindowImpl::updateDomainSelection1() {
	DOMAIN *ptr;
	if (cbo_topDomains->currentIndex() != 0) {
		txt_domainName->setText(cbo_topDomains->currentText());
		ptr = domain_list->search(cbo_topDomains->currentText().toLatin1().data());
		if (ptr != NULL) {
			txt_domainAlias->setEnabled(false);
			if (strcmp(ptr->getType(),"sym") == 0) {
				txt_domainAlias->setText(ptr->getData());
			} else {
				txt_domainAlias->clear();
			}
			user_list_create(ptr->getName(),ptr->getPWfile());
			alias_list_create(ptr->getName());
		} else {
			user_list_create("","");
			alias_list_create("");
			log("ERROR IN PTR\n");
		}
		if (!btn_domainAdd->isHidden()) {
			btn_domainAdd->hide();
		}
		btn_domainRemove->setEnabled(true);
	} else {
		txt_domainAlias->setEnabled(true);
		if (btn_domainAdd->isHidden()) {
			btn_domainAdd->show();
		}
		txt_domainName->clear();
		txt_domainAlias->clear();
		btn_domainRemove->setEnabled(false);
	}
	list_domains->setCurrentRow(cbo_topDomains->currentIndex());
}

void	MainWindowImpl::updateDomainSelection2() {
	switch(tab_mainWidget->currentIndex()) {
		case 0: //DOMAINS
			cbo_topDomains->setCurrentIndex(list_domains->currentRow());
			break;
		case 1: //USERS
			load_user_list(list_users);
			break;
		case 2: //ALIASES
			load_alias_list(list_alias);
			break;
		case 3: //LOGS
			break;
		default:
			break;
	}
}

void	MainWindowImpl::clearDomainTab() {
	list_domains->setCurrentRow(0);
	cbo_topDomains->setCurrentIndex(0);
	txt_domainName->clear();
	txt_domainAlias->clear();
}

void	MainWindowImpl::displayAliasTools() {
	if (cbx_createDomainAlias->checkState() == Qt::Checked) {
		txt_domainAlias->show();
		lbl_alias->show();
	} else {
		txt_domainAlias->hide();
		lbl_alias->hide();
	}
}
