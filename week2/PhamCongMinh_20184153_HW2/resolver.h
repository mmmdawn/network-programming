#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "validator.h"

#define RESULT_SIZE 10000

char *get_host_by_name(char *name);
char *get_host_by_addr(char *addr);
