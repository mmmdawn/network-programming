#include "resolver.h"

char *get_host_by_name(char *name) {

  if(!validate_by_regex(name, DOMAIN_REGEX))
    return "Wrong parameter: Not a domain name";

  char *IPbuffer;
  char *result = (char*)malloc(RESULT_SIZE);
  struct in_addr **pptr;
  struct hostent *hptr;

  if ((hptr = gethostbyname(name)) == NULL) {
    return "Not found information";
  }
  
  pptr = (struct in_addr**)hptr->h_addr_list;
  strcpy(result, "Official IP: ");
  strcat(result, inet_ntoa(**pptr));
  strcat(result, "\n");
  strcat(result, "Alias IP:\n");
  
  pptr++;
  for (; *pptr != NULL; pptr++ ) {
    IPbuffer = inet_ntoa(**pptr);
    strcat(result, IPbuffer);
    strcat(result, "\n");
  }

  return result;
}

char *get_host_by_addr(char *addr) {

  if(!validate_by_regex(addr, IPV4_REGEX))
    return "Wrong parameter: Not a IPv4 address";

  char *result = (char*)malloc(RESULT_SIZE);
  char **pptr;
  struct hostent *hptr;

  if ((hptr = gethostbyaddr(addr, 4, AF_INET)) == NULL) {
    return "Not found information";
  }
  
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
