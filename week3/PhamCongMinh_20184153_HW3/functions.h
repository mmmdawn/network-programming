# include "account.h"
# include "utils.h"
# include "resolver.h"

# define SIGNED_IN 1
# define NOT_SIGNED_IN 0
# define BUFFER_SIZE  1000

account activate_account(account root);
account create_account(account root);
account change_password(account, char*);
char sign_in(account root, char *username);
void search(account root);
int sign_out(char *username);
void display_homepage_domain(account root, char *username);
void display_homepage_ip(account root, char *username);

