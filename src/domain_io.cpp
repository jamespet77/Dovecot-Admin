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

#include <domain_io.h>

bool	domain_create(const char *name) {
	bool retval = false;
	char tmp[128];
	sprintf(tmp,"%s%s",ROOT_DIR,name);
	if(file_exists(tmp)) {
		//TODO: Logging of file already exists
	} else {
		if (mkdir(tmp,0750) == 0) {
			retval = true;
		} else {
			log("Error While attempting to create domain %s\n",tmp);
			//TODO: Logging of file xcreation failed
		}
	}
	return retval;
}

bool	domain_update(const char *oldname, const char *name) {
	bool retval = false;
	char cmd[256];
	char tmp[128];
	char tmp2[128];
	sprintf(tmp,"%s%s",ROOT_DIR,oldname);

	if(file_exists(tmp)) {
		sprintf(tmp2,"%s%s",ROOT_DIR,name);
		sprintf(cmd,"mv %s %s",tmp, tmp2);
		if (system(cmd) == 0) {
			retval = true;
		} else {
			//TODO: add error logs
		}
	} else {
		log("File does not exist: %s\n",cmd);
		//TODO: Logging of file does not exists
	}
	return retval;
}

bool	domain_remove(const char *name) {
	bool retval = false;
	char cmd[256];
	char tmp[128];
	sprintf(tmp,"%s%s",ROOT_DIR,name);
	
	if(file_exists(tmp)) {
		sprintf(cmd,"rm -rf %s",tmp);
		if (system(cmd) == 0) {
			retval = true;
		} else {
			//TODO: add error logs
		}
	} else {
		log("File does not exist: %s\n",cmd);
		//TODO: Logging of file does not exists
	}
	return retval;
}

bool	domain_create_alias(const char *orig, const char *alias) {
	bool retval = false;
	char cmd[256];
	char tmpO[128];
	char tmpA[128];
	sprintf(tmpO,"%s%s",ROOT_DIR,orig);
	sprintf(tmpA,"%s%s",ROOT_DIR,alias);
	if (file_exists(tmpO) && !file_exists(tmpA)) {
		sprintf(cmd,"ln -s %s %s", tmpO, tmpA);
		if (system(cmd) == 0) {
			retval = true;
		} else {
			//TODO: error alias create failed
		}
	} else {
		//TODO: alias existed or orig file did not.
		log("%s exists or %s does not:\n",tmpA,tmpO);
	}
	
	return retval;
}

void	domain_typedata(DOMAIN *node, const char *info) {
	char tmp[256];
	bool capture = false;
	int j = 0;
	if (strstr(info, "symbolic") != NULL) {
		node->setType("sym");
		for (unsigned int i = 0; i < strlen(info); i++) {
			if (capture) {
				if (info[i] != '\'' && info[i] != '\n') {
					tmp[j++] = info[i];
				}
			} else {	
				if (info[i] == '`') {
					capture = true;
				}
			}
		}
	} else {
		node->setType("dir");
	}
	tmp[j] = '\0';
	node->setData(tmp);
}

void	domain_list_create() {
	DOMAIN *node;
	char buf[2048];
	char typebuf[128];
	char row[128];
	int j = 0;

	system_cmd(buf,"ls %s",ROOT_DIR);
	domain_list = new slinkedListType<DOMAIN>;
	for (unsigned int i = 0; i < strlen(buf); i++) {
		if (buf[i] != '\n') {
			row[j++] = buf[i];
		} else {
			row[j] = '\0';
			j = 0;
			node = new DOMAIN(row,"vpasswd");
			system_cmd(typebuf,"file %s%s",ROOT_DIR,row);
			domain_typedata(node,typebuf);
			domain_list->insertLast(*node);
		}
	}
}
