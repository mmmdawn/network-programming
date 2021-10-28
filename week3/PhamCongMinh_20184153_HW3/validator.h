# include <stdio.h>
# include <regex.h>

# define IPV4_REGEX "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
# define DOMAIN_REGEX "^([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9]\\.)+[A-Za-z]{2,6}$"
# define USERNAME_REGEX "^[a-zA-Z0-9_]{1,16}$"
# define PASSWORD_REGEX "^[a-zA-Z0-9?_!@#$%^&*?]{1,16}$"

# define NOT_MATCH 0
# define MATCH 1

int validate_by_regex(char *string, char *regex);
