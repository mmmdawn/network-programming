# include <stdio.h>
# include <regex.h>

# define IPV4_REGEX "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
# define DOMAIN_REGEX "^([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9]\\.)+[A-Za-z]{2,6}$"

int validate_by_regex(char *string, char *regex);
