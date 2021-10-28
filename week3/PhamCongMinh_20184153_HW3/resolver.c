#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "resolver.h"

char *get_domain_name(char *input) {
  char *result = (char*)malloc(RESULT_SIZE);
  char **pptr;
  struct hostent *hptr;

  if(validate_by_regex(input, IPV4_REGEX))
    if ((hptr = gethostbyaddr(input, 4, AF_INET)) == NULL)
      return "Domain name not found.\n";
  
  if(validate_by_regex(input, DOMAIN_REGEX))
    if ((hptr = gethostbyname(input)) == NULL)
      return "Domain name not found.\n";

  strcpy(result, "Official name: ");
  strcat(result, hptr->h_name);
  strcat(result, "\n");
  strcat(result, "Alias name:\n");
  
  pptr = hptr->h_aliases;
  for (; *pptr != NULL; pptr++ ) {
    strcat(result, *pptr);
    strcat(result, "\n");
  }
  return result;
}

char *get_ip_address(char *input){
  char *result = (char*)malloc(RESULT_SIZE);
  struct in_addr **pptr;
  struct hostent *hptr;

  if(validate_by_regex(input, DOMAIN_REGEX))
    if ((hptr = gethostbyname(input)) == NULL)
      return "IP address not found.\n";

  if(validate_by_regex(input, IPV4_REGEX))
    if ((hptr = gethostbyaddr(input, 4, AF_INET)) == NULL)
      return "IP address not found.\n";
  
  pptr = (struct in_addr**)hptr->h_addr_list;
  strcpy(result, "IP address:\n");
  
  for (; *pptr != NULL; pptr++ ) {
    strcat(result, inet_ntoa(**pptr));
    strcat(result, "\n");
  }

  return result;
}
