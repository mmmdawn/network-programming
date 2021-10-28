#define MAX_DOMAIN_LEN 253
#define LOGIN_INFO_LEN 16


struct struct_account {
  char username[LOGIN_INFO_LEN];
  char password[LOGIN_INFO_LEN];
  char homepage[MAX_DOMAIN_LEN];
  char status;
  char activation_attemp;
  char login_attemp;
  struct struct_account *next;
};

typedef struct struct_account *account;

void write_to_file(account root);
account load_file();
account create_node(char *username, char *password, char *homepage, char status, char activation_attemp, char login_attemp);
account find_by_username(account root, char *username);
