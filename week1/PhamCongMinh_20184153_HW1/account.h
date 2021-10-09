#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct struct_account {
  char username[24];
  char password[24];
  char status;
  struct struct_account *next;
};

typedef struct struct_account *account;

void write_to_file(account root);
account load_file();
account create_node(char *username, char *password, char status);
account find_by_username(account root, char *username);
