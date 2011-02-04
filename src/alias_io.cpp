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

#include <alias_io.h>

bool	alias_create(ALIAS *alias, const char *domain) {
	bool retval = false;
	char tmpUserDir[128];
	sprintf(tmpUserDir,"%s/%s/%s",ROOT_DIR,domain,alias->getAliasName());
	if (file_exists(tmpUserDir)) {
		log("File already exists: %s\n",tmpUserDir);
		retval = true;
	}
	if (alias_exists(alias->getAliasName(),domain)) {
		log("User already exists: %s@%s\n",alias->getAliasName(),domain);
		retval = true;
	}

	if (mkdir(tmpUserDir,0750) == 0) {
	//all is good in the hood!	
		log("Created alias dir: %s\n",tmpUserDir);
		retval = true;
	} else {
		log("Error while Creating alias Dir: %s\n",tmpUserDir);
	}
	return retval;
}

bool	alias_remove(ALIAS *alias, const char *domain) {
	bool retval = false;
	char tmpUserDir[128];
	char cmd[128];

	sprintf(tmpUserDir,"%s/%s/%s",ROOT_DIR,domain,alias->getAliasName());
	if (file_exists(tmpUserDir)) {
		sprintf(cmd,"rm -rf %s",tmpUserDir);
		if (system(cmd)) {
		//all is good in the hood!	
			retval = true;
		} else {
			log("Error while removing alias Dir: %s\n",tmpUserDir);
		}
	}
	return retval;
}

void	alias_get_forward(char *file, ALIAS *alias, const char *domain) {
	FILE *fh;
	char tmp[256];
	char *row = NULL;
	size_t len = 0;

	const char fwfile[10] = ".forward";
	
	strcpy(file,"");
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),fwfile);

	if (!file_exists(tmp)) {
		alias_create_forward(alias,domain);
	}
	fh = fopen(tmp,"r");
	if (fh != NULL) {
		getline(&row, &len,fh);
		if (strncmp(row,"# Exim filter",13) != 0) {
			log("%s %s file is malformed:\n",alias->getAliasName(),fwfile);
		}
		while(getline(&row, &len,fh) != EOF) {
			strcat(file,row);
		}
		fclose(fh);
	} else {
		strcpy(file,"");
	}
}

bool	alias_create_forward(ALIAS *alias, const char *domain) {
	bool retval = false;
	FILE *fh;
	char tmp[256];
	const char fwfile[10] = ".forward";
	
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),fwfile);
	fh = fopen(tmp,"w");
	if (fh != NULL) {
		fputs("# Exim filter << ===  DO NOT REMOVE THIS\n",fh);
		fclose(fh);
	}
	return retval;
}

bool	alias_update_forward(const char *file, ALIAS *alias, const char *domain) {
	bool retval = false;
	FILE *fh;
	char str[256];
	const char fwfile[10] = ".forward";

	sprintf(str,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),fwfile);
	alias_create_forward(alias, domain);
	fh = fopen(str,"a");
	if (fh != NULL) {
		fputs(file,fh);
		fclose(fh);
		retval = true;
	} else {
		log("Could not open file: %s\n",str);
	}
	
	return retval;
}

void	alias_get_whitelist(char *file, ALIAS *alias, const char *domain) {
	FILE *fh;
	char tmp[256];
	char *row = NULL;
	size_t len = 0;

	const char wlfile[10] = "whitelist";
	
	strcpy(file,"");
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),wlfile);

	if (!file_exists(tmp)) {
		alias_create_whitelist(alias,domain);
	}
	fh = fopen(tmp,"r");
	if (fh != NULL) {
		while(getline(&row, &len,fh) != EOF) {
			strcat(file,row);
		}
		fclose(fh);
	} else {
		strcpy(file,"");
	}
}

bool	alias_create_whitelist(ALIAS *alias, const char *domain) {
	bool retval = false;
	FILE *fh;
	char tmp[256];
	const char wlfile[10] = "whitelist";
	
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),wlfile);
	fh = fopen(tmp,"w");
	if (fh != NULL) {
		fclose(fh);
	}
	return retval;
}

bool	alias_update_whitelist(const char *file, ALIAS *alias, const char *domain) {
	bool retval = false;
	FILE *fh;
	char str[256];
	const char wlfile[10] = "whitelist";

	sprintf(str,"%s/%s/%s/%s",ROOT_DIR,domain,alias->getAliasName(),wlfile);
	alias_create_whitelist(alias, domain);
	fh = fopen(str,"a");
	if (fh != NULL) {
		fputs(file,fh);
		fclose(fh);
		retval = true;
	} else {
		log("Could not open file: %s\n",str);
	}
	
	return retval;
}

bool	alias_exists(const char *alias, const char *domain) {
	bool retval = false;
	char cmd[256];
	sprintf(cmd,"%s/%s/%s",ROOT_DIR,domain,alias);
	if (file_exists(cmd)) {
		retval = true;
	}
	return retval;
}

void	alias_list_create(const char *domain) {
	ALIAS *node;
	USER *user;
	char cmd[256];
	char buf[4096];
	char typebuf[128];
	char row[128];
	int j = 0;

	system_cmd(buf,"ls %s/%s",ROOT_DIR,domain);
	alias_list = new slinkedListType<ALIAS>;
	for (unsigned int i = 0; i < strlen(buf); i++) {
		if (buf[i] != '\n') {
			row[j++] = buf[i];
		} else {
			row[j] = '\0';
			j = 0;
			user = new USER;
			user->setUserName(row);
			if (	strncmp(row,"vpasswd",7) != 0 && 
					strcmp(row,"Maildir") != 0 && 
					strcmp(row,"Mailbox") != 0 && 
					strncmp(row,"_",1) != 0 &&
					user_list->search(*user) == NULL
					) {
				node = new ALIAS(row);
				alias_list->insertLast(*node);
			}
		}
	}
	//SORT IS REMOVING ENTRIES
	//THIS IS A HACK TO PREVENT THAT
//	ALIAS *hack;
//	hack = new ALIAS("aaaaaaaaaaaaaaaaa","aaaaa");
//	alias_list->insertFirst(*hack);
//	alias_list->sort();
//	alias_list->deleteNode(*hack);
}

