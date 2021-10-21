# include "validator.h"

int validate_by_regex(char *string, char *regex) {
  char msgbuf[100];
  regex_t preg;
  int result;
  int ret;

  ret = regcomp(&preg, regex, REG_EXTENDED);
  if (ret) {
    fprintf(stderr, "Could not compile regex\n");
    return 0;
  }

  ret = regexec(&preg, string, 0, NULL, 0);
  
  if ( ret == _REG_NOMATCH ) result = 0;  // NOT MATCH
  else if ( ret == 0 ) result = 1;  // MATCH
  else {
    regerror(ret, &preg, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    result = 0;
  }

  regfree(&preg);
  return result;
}
