#include <globals.h>

//JUST A NOTE
//These are static till app is working correctly
//add then I'll add a config file
char ROOT_DIR[1024] = "/home/dovecot/domains/";
char LOG_DIR[128] = "/var/log/";
char LOG_FILE[128] = "dca";
char LOG_LOCK[32] = "dca_log.lock";
bool LOGGING = false;
char DCPW[128] = "/usr/sbin/dovecotpw";
char UID[32] = "vmail";
char GID[32] = "vmail";

CONFIG_MAP config;

slinkedListType<DOMAIN> *domain_list;
slinkedListType<USER> *user_list;
slinkedListType<ALIAS> *alias_list;
