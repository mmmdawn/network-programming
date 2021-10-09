# include "account.h"

account create_node(char *username, char *password, char status) {
  account acc = (account)malloc(sizeof(struct struct_account));
  strcpy(acc->username, username);
  strcpy(acc->password, password);
  acc->status = status;
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
    fprintf(fp, "%s %s %c\n", temp->username, temp->password, temp->status);
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

  account root = create_node("","",' ');
  account temp = root;
  char username[24];
  char password[24];
  char status;

  while (!feof(fp)) {
    fscanf(fp, "%s %s %c\n", username, password, &status);
    temp->next = create_node(username,password, status);
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
