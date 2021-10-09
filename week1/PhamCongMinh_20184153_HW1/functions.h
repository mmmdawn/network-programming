# include "account.h"

# define SIGNED_IN 1
# define NOT_SIGNED_IN 0
# define BUFFER_SIZE  1000
# define LOGIN_INFO_SIZE  24

account activate_account(account, char*, char*, char*);
account create_account(account root);
account change_password(account, char*);
char sign_in(account, char**, char*, int*);
void search(account, char*);


