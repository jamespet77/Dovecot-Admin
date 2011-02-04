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

#include <user_io.h>

bool	user_create(USER *user, const char *domain, const char *pwfile) {
	bool retval = false;
	char tmpUserDir[128];
	sprintf(tmpUserDir,"%s/%s/%s",ROOT_DIR,domain,user->getUserName());
	if (file_exists(tmpUserDir)) {
		log("File already exists: %s\n",tmpUserDir);
		retval = true;
	}
	if (user_exists(user->getUserName(),domain,pwfile)) {
		log("User already exists: %s@%s\n",user->getUserName(),domain);
		retval = true;
	}
	if (!user_create_pw(user,domain,pwfile)) {
		log("Error Creating user passwd:\n");
	}

	if (mkdir(tmpUserDir,0750) == 0) {
	//all is good in the hood!	
		log("Created user dir: %s\n",tmpUserDir);
		retval = true;
	} else {
		log("Error while Creating user Dir: %s\n",tmpUserDir);
	}
	return retval;
}

bool	user_remove(USER *user, const char *domain, const char *pwfile) {
	bool retval = false;
	char tmpUserDir[128];
	sprintf(tmpUserDir,"%s/%s/%s",ROOT_DIR,domain,user->getUserName());

//Implement after dir delete verification is running
//	if (file_exists(tmpUserDir)) {
//		if (mkdir(tmpUserDir,0750) == 0) {
//		//all is good in the hood!	
//			retval = true;
//		} else {
//			log("Error while Creating user Dir: %s\n",tmpUserDir);
//		}
//	}
	if (user_exists(user->getUserName(),domain,pwfile)) {
		if (user_remove_pw(user,domain,pwfile)) {
			log("User removed from %s\n",pwfile);
			retval = true;
		} else {
			log("Error in removing user from %s\n",pwfile);
		}
	} else {
		log("User does not exist for removal\n");
	}
	return retval;
}

bool	user_create_pw(USER *user, const char *domain, const char *pwfile) {
//uname:passwd:uid:gid:fullname:homedir:NOQUOTA:pass_decypt
//%s:%s:%s:%s:%s:%s:NOQUOTA:%s
	bool retval = false;
	FILE *fh;
	char str[256];
	char tmpStr[1024];
	char pwd[128];
	//check if user exists
	if (!user_exists(user->getUserName(),domain,pwfile)) {
		//user does nto exist - continue
		sprintf(str,"%s/%s/%s",ROOT_DIR,domain,pwfile);
		if (create_passwd(pwd,user->getPasswd())) {
			fh = fopen(str,"a");
			if (fh != NULL) {
				sprintf(tmpStr,"%s:%s:%s:%s:%s:%s:NOQUOTA:%s\n",
						user->getUserName(),
						pwd,
						UID,GID,
						user->getRealName(),
						user->getHomeDir(),
						user->getPasswd());
	
				fputs(tmpStr,fh);
				fclose(fh);
				log("User added to %s",str);
				retval = true;
			} else {
				log("Could not open file: %s\n",str);
			}
		} else {
			log("Could not create user:\n");
		}
	} else {
		log("User Exists\n");
	}	
	
	return retval;
}

bool	user_remove_pw(USER *user, const char *domain, const char *pwfile) {
	FILE *fin;
	FILE *fout;
	char str[128];
	char tmp[128];
	char *row = NULL;
	size_t len = 0;
	bool done = false;
	unsigned int i;

	sprintf(str,"%s/%s/%s",ROOT_DIR,domain,pwfile);

	fin = fopen(str,"r");
	if (fin != NULL) {
		fout = fopen("/tmp/purple","w");
		while(getline(&row, &len,fin) != EOF) {
			done = false;
			for(i = 0; !done; i++) {
				if (row[i] == ':' || i >= 127) {
					done = true;
				}
			}
			strncpy(tmp,&row[0],i - 1);
			tmp[i - 1] = '\0';
			if (strcmp(user->getUserName(),tmp) != 0) {
				fputs(row,fout);
			}
		}
		if (row) free(row);
		fclose(fout);
		fclose(fin);
		log("%s modified: %s removed",str,user->getUserName());
		sprintf(tmp,"mv /tmp/purple %s", str);
		system(tmp);
	}

	return !user_exists(user->getUserName(), domain, pwfile);
}

bool	user_update_pw(USER *user, const char *domain, const char *pwfile) {
	return (user_remove_pw(user,domain,pwfile) &&
	user_create_pw(user,domain,pwfile));
}

void	user_get_forward(char *file, USER *user, const char *domain) {
	FILE *fh;
	char tmp[256];
	char *row = NULL;
	size_t len = 0;

	const char fwfile[10] = ".forward";
	
	strcpy(file,"");
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),fwfile);

	if (!file_exists(tmp)) {
		user_create_forward(user,domain);
	}
	fh = fopen(tmp,"r");
	if (fh != NULL) {
		getline(&row, &len,fh);
		if (strncmp(row,"# Exim filter",13) != 0) {
			log("%s %s file is malformed:\n",user->getUserName(),fwfile);
		}
		while(getline(&row, &len,fh) != EOF) {
			strcat(file,row);
		}
		fclose(fh);
	} else {
		strcpy(file,"");
	}
}

bool	user_create_forward(USER *user, const char *domain) {
	bool retval = false;
	FILE *fh;
	char tmp[256];
	const char fwfile[10] = ".forward";
	
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),fwfile);
	fh = fopen(tmp,"w");
	if (fh != NULL) {
		fputs("# Exim filter << ===  DO NOT REMOVE THIS\n",fh);
		fclose(fh);
	}
	return retval;
}

bool	user_update_forward(const char *file, USER *user, const char *domain) {
	bool retval = false;
	FILE *fh;
	char str[256];
	const char fwfile[10] = ".forward";

	sprintf(str,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),fwfile);
	user_create_forward(user, domain);
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


void	user_get_whitelist(char *file, USER *user, const char *domain) {
	FILE *fh;
	char tmp[256];
	char *row = NULL;
	size_t len = 0;

	const char wlfile[10] = "whitelist";
	
	strcpy(file,"");
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),wlfile);

	if (!file_exists(tmp)) {
		user_create_whitelist(user,domain);
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

bool	user_create_whitelist(USER *user, const char *domain) {
	bool retval = false;
	FILE *fh;
	char tmp[256];
	const char wlfile[10] = "whitelist";
	
	sprintf(tmp,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),wlfile);
	fh = fopen(tmp,"w");
	if (fh != NULL) {
		fclose(fh);
	}
	return retval;
}

bool	user_update_whitelist(const char *file, USER *user, const char *domain) {
	bool retval = false;
	FILE *fh;
	char str[256];
	const char wlfile[10] = "whitelist";

	sprintf(str,"%s/%s/%s/%s",ROOT_DIR,domain,user->getUserName(),wlfile);
	user_create_whitelist(user, domain);
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


bool	user_exists(const char *user, const char *domain, const char *pwfile) {
	bool retVal = false;
	FILE *fh;
	unsigned int i;
	char *row = NULL;
	char tmpU[128];
	char cmd[128];
	size_t len = 0;
	bool done = false;

	sprintf(cmd,"%s/%s/%s",ROOT_DIR,domain,pwfile);
	fh = fopen(cmd,"r");
	retVal = false;

	if (fh != NULL) {
		while(getline(&row,&len,fh) != EOF) {
			done = false;
			for (i = 0; !done; i++) {
				if (row[i] == ':' || i >= 127) {
					done = true;
				}
			}
			strncpy(tmpU, &row[0], i - 1);
			tmpU[i - 1] = '\0';
			if (strcmp(user,tmpU) == 0) {
				return true;
			}
		}
		//Release allocated mem
		if (row) free(row);
		fclose (fh);
	}
	return retVal;
}

bool	create_passwd(char *outfile, const char *infile) {
	bool retval = false;
	if (file_exists(DCPW)) {
		system_cmd(outfile,"%s -p %s -s md5",DCPW,infile);
		printf("%s\n",outfile);
		strncpy(outfile, &outfile[5], 35);
		outfile[35] = '\0';
		cleanNewLine(outfile);
		printf("%s\n",outfile);
		retval = true;
	}
	return retval;
}

void	user_list_create(const char *domain, const char *pwfile) {
	USER *node;
	FILE *fh;
	char cmd[256];
	char buf[128];
	char pwRow[8][128];
	char *row = NULL;
	size_t len = 0;
	int j = 0,k = 0;;

	sprintf(cmd,"%s/%s/%s",ROOT_DIR,domain,pwfile);
	fh = fopen(cmd,"r");

	user_list = new slinkedListType<USER>;
	if (fh != NULL) {
		while(getline(&row,&len,fh) != EOF) {
			k = 0;
			node = new USER;
			for(unsigned int i = 0;i < strlen(row); i++) {
				if (row[i] == ':' || row[i] == '\n'|| row[i] == EOF) {
					if (j == 0) {
						strcpy(pwRow[k++],"");
					} else {
						buf[j] = '\0';
						strcpy(pwRow[k++],buf);
						j = 0;
					}
				} else {
					buf[j++] = row[i];
				}
			}
			buf[j] = '\0';
			strcpy(pwRow[k],buf);

			//Set USER vars
			node->setUserName(pwRow[0]);
			node->setPasswd(pwRow[7]);
			node->setHomeDir(pwRow[5]);
			node->setRealName(pwRow[4]);
			user_list->insertLast(*node);
		}
		if (row) free(row);
	} else {
		log("ERROR in FILE OPEN: %s\n",cmd);
	}
	//SORT IS REMOVING ENTRIES
	//THIS IS A HACK TO PREVENT THAT
//	USER *hack;
//	hack = new USER("aaaa","aaaaaaaaaaaaaaaaaa","aaaaaa","aaaaaaa");
//	user_list->insertFirst(*hack);
//	user_list->sort();
//	user_list->deleteNode(*hack);
}

