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

#include <utils.h>

void 	sys_cmd(const char *input, char *buffer) {
	FILE *FH;
	unsigned int i = 0;
	if ((FH = popen(input, "r")) != NULL) {
		__gnu_cxx::stdio_filebuf<char> fb(FH, ios::in) ;
		istream f(&fb);
		for (char c = f.get(); !f.eof(); c = f.get()) {
			buffer[i++] = c;
		}
		buffer[i] = '\0';
		pclose(FH);
	}
}

void	system_cmd(char *buffer, const char *input, ...) {
	FILE *FH;
	va_list fmtargs;
	char buf[256];
	unsigned int i = 0;

	va_start(fmtargs,input);
	vsnprintf(buf,sizeof(buf) - 1, input, fmtargs);
	va_end(fmtargs);

	if ((FH = popen(buf, "r")) != NULL) {
		__gnu_cxx::stdio_filebuf<char> fb(FH, ios::in) ;
		istream f(&fb);
		for (char c = f.get(); !f.eof(); c = f.get()) {
			buffer[i++] = c;
		}
		buffer[i] = '\0';
		pclose(FH);
	}
}

char	*lowercase(char *str) {
	for(unsigned int x = 0;x < strlen(str); x++) {
		str[x] = tolower(str[x]);
	}
	return &str[0];
}

char	*uppercase(char *str) {
	for(unsigned int x = 0;x < strlen(str); x++) {
		str[x] = toupper(str[x]);
	}
	return &str[0];
}

bool	file_exists(const char *file) {
	bool retval = false;
	struct stat file_stat;
	if(stat(file,&file_stat) == 0) {
		retval = true;
	}
	return retval;
}

void    load_config(CONFIG_MAP &conf) {
	FILE *fp;
	char str1[256];
	char str2[256];
	char *row = NULL;
	size_t len = 0;
	char tmpStr[1024];
	bool done = false;
	char conf_file[16] = "dca.conf";
	char *conf_dir[] = {
		"./","/etc/","/etc/dovecot/","/usr","/usr/local/",
		"/usr/dovecot/"
	};

	for (unsigned int i = 0; i < 6 && !done; i++) {
		sprintf(tmpStr,"%s/%s",conf_dir[i],conf_file);
		if (file_exists(tmpStr)) {
			done = true;
		}
	}
	if (done) {
		fp = fopen(tmpStr,"r");
		if (fp != NULL) {
			while(getline(&row, &len,fp) != EOF) {
				str1[0] = '\0';
				str2[0] = '\0';
				clean(row);
				if (isalnum(row[0])) {
					split(row,str1,str2,'=');
					conf[str1] = str2;
				}
			}
		}
	} else {
		printf("failure loging config file\n");
	} 
}

void	clean(char *str) {
	char tmp[1024];
	bool first = false;
	unsigned int j = 0;
	for(unsigned int i = 0; i < strlen(str); i++) {
		if (first) {
			if (isalnum(str[i]) || str[i] == '=' || str[i] == '_' || str[i] == '.' || str[i] == '/') {
				tmp[j++] = str[i];
			}
		} else {
			if (str[i] == ' ') {
			} else if (str[i] == '#') {
				i = strlen(str);
			} else if (isalnum(str[i])) {
				first = true;
				tmp[j++] = str[i];
			} else {
			}
		}
	}
	tmp[j] = '\0';
	strcpy(str,tmp);
}

void	cleanNewLine(char *str) {
	char tmp[2048];
	unsigned int j = 0;
	for(unsigned int x = 0;x < strlen(str); x++) {
		if(str[x] != '\n' && str[x] != '\r') {
			tmp[j++] = str[x];
		}
	}
	tmp[j] = '\0';
	sprintf(str,"%s",&tmp[0]);
}

void	split(const char *input,char *str1, char *str2, const char delim) {
	bool value = false;
	unsigned int j = 0;
	for(unsigned int i = 0; i < strlen(input); i++) {
		if (!value) {
			if (input[i] != delim) {
				str1[j++] = input[i];
			} else {
				value = true;
				str1[j] = '\0';
				j = 0;
			}
		} else {
			str2[j++] = input[i];
		}
	}
	str2[j] = '\0';
}

void	folderSize(char *buf, const char *file) {
	char tmp[512];
	unsigned int j = 0;
	if (file_exists(file)) {
		system_cmd(tmp,"du -h %s --max-depth=0",file);
		for(unsigned int i = 0;i < strlen(tmp); i++) {
			if (tmp[i] == ' ' || tmp[i] == '\t') {
				buf[j] = '\0';
				return;
			} else {
				buf[j++] = tmp[i];
			}
		}
	} else  {
		strcpy(buf,"0 K");
	}
}

void	fileLastAccess(char *buf, const char *file) {
	char *row = NULL;
	size_t len = 0;
	char tmp[512];
	if (file_exists(file)) {
		system_cmd(tmp,"dca_access.pl %s/Maildir/dovecot.index",file);
		strcpy(buf,tmp);
	} else  {
		strcpy(buf,"Never");
	}
}

//void sleep( clock_t wait ) {
//	clock_t goal;
//	goal = wait + clock();
//	while( goal > clock() )
//	;
//}
