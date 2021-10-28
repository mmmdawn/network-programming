#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

account create_node(char *username, char *password, char *homepage, char status, char activation_attemp, char login_attemp) {

  account acc = (account)malloc(sizeof(struct struct_account));
  strcpy(acc->username, username);
  strcpy(acc->password, password);
  strcpy(acc->homepage, homepage);

  acc->status = status;
  acc->activation_attemp = activation_attemp;
  acc->login_attemp = login_attemp;
  acc->next = NULL;

  return acc;
} 

account find_by_username(account root, char *username) {
  account temp = root;
  while (temp != NULL) {
    if (strcmp(temp->username, username) == 0) return temp;
    temp = temp->next;
  }
  return NULL;
}

void write_to_file(account root) {
  account temp = root;
  FILE *fp = fopen("account.txt", "w");
  while ( temp != NULL ) {
    fprintf(fp, "%s %s %c %c %c %s\n", temp->username, temp->password, temp->status, 
        temp->activation_attemp, temp->login_attemp, temp->homepage);
    temp = temp->next;
  }

  fclose(fp);
}

account load_file() {
  FILE *fp = fopen("account.txt", "r");
  if (!fp) {
    printf("\n\nFile does not exist\n");
    return NULL;
  }

  account root = create_node("","","",0,0,0);
  account temp = root;
  char username[LOGIN_INFO_LEN];
  char password[LOGIN_INFO_LEN];
  char homepage[MAX_DOMAIN_LEN];
  char status;
  char activation_attemp;
  char login_attemp;

  while (!feof(fp)) {
    fscanf(fp, "%s %s %c %c %c %s\n", username, password, &status, &activation_attemp, &login_attemp, homepage);
    temp->next = create_node(username,password,homepage,status,activation_attemp,login_attemp);
    temp = temp->next;
  }

  temp = root->next;
  /* while (temp != NULL) { */
  /*   printf("%s %s %c\n", temp->username, temp->password, temp->status); */
  /*   temp = temp->next; */
  /* } */
  free(root);
  fclose(fp);
  return temp;
}
