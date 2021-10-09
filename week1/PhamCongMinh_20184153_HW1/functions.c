#include "functions.h"

/*
 * Function 1: Create account
 * Create a new node and append to the account list
 * */
account create_account(account root) {
  char username[LOGIN_INFO_SIZE];
  char password[LOGIN_INFO_SIZE];
  char password1[LOGIN_INFO_SIZE];

  printf("\nCREATING NEW ACCOUNT\n-----------\n");
  printf("Enter username: ");
  scanf("%s",username);

  account temp = find_by_username(root, username);
  if ( temp ) {
    printf("\n\nAccount Existed.\n");
    return root;
  }

  printf("Enter password: ");
  scanf("%s",password);
  printf("Confirm password: ");
  scanf("%s", password1);

  if (strcmp(password1, password)) {
    printf("\n\nIncorrect.\n");
    return root;
  }

  account acc = create_node(username, password, '2');
  temp = root;

  while (temp->next != NULL) temp = temp->next;
  temp->next = acc;
  write_to_file(root);
  printf("\nSuccessful registration. Activation required.\n");

  return root;
}


/*
 * Function 2: Activate account
 * */
account activate_account(account root, char *username, char *password, char* code) {
  int code_is_valid = 1;
  account temp = find_by_username(root, username);

  if ( (!temp) || (strcmp(temp->password, password)) ) {
    printf("\n\nInvalid Login Credentials.\n");
    return root;
  }

  if (temp->status == '0' || temp->status == '1') {
    printf("\n\nThis account has been activated before.\n");
    return root;
  }


  // An activation code is valid when it has 8 digit characters.
  if ( strlen(code) != 8 ) code_is_valid = 0;
  for (int i = 0; i < strlen(code); ++i) {
    if (code[i] < '0' && code[i] > '9')
      code_is_valid = 0;
  }

  if ( !code_is_valid ) {
    if (temp-> status < '6') {
      printf("\n\nAccount is not activated.\n");
      temp->status += 1;
    } else {
      printf("\n\nActivation code is incorrect.\nAccount is blocked.\n");
      temp->status = '0';
    }
    write_to_file(root);
    return root;
  }

  printf("\n\nAccount is activated.\n");
  temp->status = '1';
  write_to_file(root);
  return root;
}


/*
 * Function 3: Sign in
 * */
char sign_in(account root, char **usernames, char *attemps, int *pos) {
  char username[LOGIN_INFO_SIZE];
  char password[LOGIN_INFO_SIZE];

  printf("SIGN IN\n-----------\n");
  printf("Username: ");
  scanf("%s", username);
  account temp = find_by_username(root, username);
  if ( !temp ) {
    printf("\n\nCannot find account.\n");
    return NOT_SIGNED_IN;
  }
    
  if ( temp->status == '0' ) {
    printf("\n\nAccount is blocked.\n");
    return NOT_SIGNED_IN;
  }

  int i = 0;
  while (strcmp(usernames[i], "")) {
    if ( !strcmp(usernames[i], username) ) {
      break;
    }
    i++;
  }

  if (!strcmp(usernames[i], "")) {
    strcpy(usernames[i], username);
  }

  printf("Password: ");
  scanf("%s", password);
  if ( strcmp(temp->password, password ) ) {
    if (attemps[i] < 3) {
      printf("\n\nPassword is incorrect.\n");
      attemps[i] += 1;
    } else {
      printf("\n\nPassword is incorrect.\nAccount is blocked.\n");
      temp->status = '0';
      write_to_file(root);
    }
    return NOT_SIGNED_IN;
  }

  printf("\n\nHello %s\n", temp->username);
  *pos = i;
  attemps[i] = 0;
  return SIGNED_IN;
}

/*
 * Function 4: Search
 * */
void search(account root, char* username) {
  account temp = find_by_username(root, username);
  if (!temp) {
    printf("\n\nCannot find account.\n");
    return;
  }

  switch (temp->status) {
    case '0':
      printf("\n\nAccount is blocked.\n");
      break;
    case '1':
      printf("\n\nAccount is activated.\n");
      break;
    default:
      printf("\n\nAccount is not activted.\n");
  }
}

/*
 * Function 5: Change password
 * */
account change_password(account root, char *username) {
  char password[LOGIN_INFO_SIZE];
  char password1[LOGIN_INFO_SIZE];
  char password2[LOGIN_INFO_SIZE];

  account temp = find_by_username(root, username);

  printf("\nCHANGE PASSWORD\n-----------\n");
  printf("Enter current password: ");
  scanf("%s", password);

  if (strcmp(password, temp->password)) {
    printf("\n\nCurrent password is incorrect. Please try again.\n");
    return root;
  }

  printf("Enter new password: ");
  scanf("%s", password1);
  printf("Confirm new password: ");
  scanf("%s", password2);

  if (strcmp(password1, password2)) {
    printf("\n\nIncorrect.\n");
    return root;
  }
  
  printf("\n\nPassword is changed.\n");
  strcpy(temp->password, password1);
  write_to_file(root);
  return root;
}

