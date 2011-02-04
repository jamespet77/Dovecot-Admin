#ifndef GLOBALS_HH
#define GLOBALS_HH

#include <stdio.h>
#include <pwd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <domain.h>
#include <domain_io.h>
#include <user.h>
#include <user_io.h>
#include <alias.h>
#include <alias_io.h>
#include <slinkedList.h>
#include <map>

extern char ROOT_DIR[1024];
extern char LOG_DIR[128];
extern char LOG_FILE[128];
extern bool LOGGING;
extern char LOG_LOCK[32];
extern char DCPW[128];
extern char UID[32];
extern char GID[32];
extern passwd *dc_uid;
typedef map<char *,char *> CONFIG_MAP;;
extern CONFIG_MAP config;

extern slinkedListType<DOMAIN> *domain_list;
extern slinkedListType<USER> *user_list;
extern slinkedListType<ALIAS> *alias_list;

#endif
