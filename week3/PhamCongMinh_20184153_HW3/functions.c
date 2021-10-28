#include <string.h>
#include "functions.h"

/*
 * Function 1: Create account
 * Create a new node and append to the account list
 * */
account create_account(account root) {
  char username[BUFFER_SIZE];
  char password[BUFFER_SIZE];
  char password1[BUFFER_SIZE];
  char homepage[BUFFER_SIZE];

  printf("\nCREATING NEW ACCOUNT\n-----------\n");
  printf("Enter username: ");
  fgets(username, BUFFER_SIZE, stdin);
  username[strlen(username) - 1] = '\0';

  if (!validate_by_regex(username, USERNAME_REGEX)) {
    printf("\n\nInvalid username.\n");
    return root;
  }

  account temp = find_by_username(root, username);
  if ( temp ) {
    printf("\n\nAccount Existed.\n");
    return root;
  }


  printf("Enter password: ");
  fgets(password, BUFFER_SIZE, stdin);
  password[strlen(password) - 1] = '\0';

  if (!validate_by_regex(password, PASSWORD_REGEX)) {
    printf("\n\nPassword contains invalid characters.\n");
    return root;
  }

  printf("Confirm password: ");
  fgets(password1, BUFFER_SIZE, stdin);
  password1[strlen(password1) - 1] = '\0';

  if (strcmp(password1, password)) {
    printf("\n\nIncorrect.\n");
    return root;
  }

  printf("Enter homepage: ");
  fgets(homepage, BUFFER_SIZE, stdin);
  homepage[strlen(homepage) - 1] = '\0';

  if (!validate_by_regex(homepage, IPV4_REGEX) && !validate_by_regex(homepage, DOMAIN_REGEX)) {
    printf("\n\nInvalid homepage.\n");
    return root;
  }

  account acc = create_node(username, password, homepage, '2', '0', '0');
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
account activate_account(account root) {
  char username[BUFFER_SIZE];
  char password[BUFFER_SIZE];
  char code[BUFFER_SIZE];
    
  printf("\nACTIVATING ACCOUNT\n-----------\n");
  printf("Username: ");
  fgets(username, BUFFER_SIZE, stdin);
  username[strlen(username) - 1] = '\0';

  if (!validate_by_regex(username, USERNAME_REGEX)) {
    printf("\n\nInvalid username.\n");
    return root;
  }


  printf("Password: ");
  fgets(password, BUFFER_SIZE, stdin);
  password[strlen(password) - 1] = '\0';

  if (!validate_by_regex(password, PASSWORD_REGEX)) {
    printf("\n\nPassword contains invalid characters.\n");
    return root;
  }

  printf("Code: ");
  fgets(code, BUFFER_SIZE, stdin);
  code[strlen(code) - 1] = '\0';

  int code_is_valid = 1;
  account temp = find_by_username(root, username);

  if ( (!temp) || (strcmp(temp->password, password)) ) {
    printf("\n\nInvalid Login Credentials.\n");
    return root;
  }

  if (temp->status == '1') {
    printf("\n\nThis account has been activated before.\n");
    return root;
  } else if (temp->status == '0') {
    printf("\n\nThis account is blocked.\n");
    return root;
  }

  // An activation code is valid when it has 8 digit characters.
  if ( strlen(code) != 8 ) code_is_valid = 0;
  for (int i = 0; i < strlen(code); ++i) {
    if (code[i] < '0' && code[i] > '9')
      code_is_valid = 0;
  }

  if ( !code_is_valid ) {
    if (temp->activation_attemp < '4') {
      printf("\n\nAccount is not activated.\n");
      temp->activation_attemp += 1;
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
char sign_in(account root, char *usrname) {
  char username[BUFFER_SIZE];
  char password[BUFFER_SIZE];

  printf("SIGN IN\n-----------\n");
  printf("Username: ");
  fgets(username, BUFFER_SIZE, stdin);
  username[strlen(username) - 1] = '\0';

  account temp = find_by_username(root, username);
  if ( !temp ) {
    printf("\n\nCannot find account.\n");
    return NOT_SIGNED_IN;
  }
    
  if ( temp->status == '0' ) {
    printf("\n\nAccount is blocked.\n");
    return NOT_SIGNED_IN;
  }


  printf("Password: ");
  fgets(password, BUFFER_SIZE, stdin);
  password[strlen(password) - 1] = '\0';

  if ( strcmp(temp->password, password ) ) {
    if (temp->login_attemp < '3') {
      printf("\n\nPassword is incorrect.\n");
      temp->login_attemp += 1;
      write_to_file(root);
    } else {
      printf("\n\nPassword is incorrect.\nAccount is blocked.\n");
      temp->status = '0';
      write_to_file(root);
    }
    return NOT_SIGNED_IN;
  }

  printf("\n\nHello %s\n", temp->username);
  strcpy(usrname, username);
  return SIGNED_IN;
}

/*
 * Function 4: Search
 * */
void search(account root) {
  char username[BUFFER_SIZE];

  printf("\n\nSEARCH\n-----------\n");
  printf("Username: ");
  fgets(username, BUFFER_SIZE, stdin);
  username[strlen(username) - 1] = '\0';

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
  char password[BUFFER_SIZE];
  char password1[BUFFER_SIZE];
  char password2[BUFFER_SIZE];

  account temp = find_by_username(root, username);

  printf("\nCHANGE PASSWORD\n-----------\n");
  printf("Enter current password: ");
  fgets(password, BUFFER_SIZE, stdin);
  password[strlen(password) - 1] = '\0';

  if (strcmp(password, temp->password)) {
    printf("\n\nCurrent password is incorrect. Please try again.\n");
    return root;
  }

  printf("Enter new password: ");
  fgets(password1, BUFFER_SIZE, stdin);
  password1[strlen(password1) - 1] = '\0';

  if (!validate_by_regex(password1, PASSWORD_REGEX)) {
    printf("\n\nPassword contains invalid characters.\n");
    return root;
  }


  printf("Confirm new password: ");
  fgets(password2 , BUFFER_SIZE, stdin);
  password2[strlen(password2) - 1] = '\0';

  if (strcmp(password1, password2)) {
    printf("\n\nIncorrect.\n");
    return root;
  }
  
  printf("\n\nPassword is changed.\n");
  strcpy(temp->password, password1);
  write_to_file(root);
  return root;
}


/*
 * Function 6: Sign out
 * */
int sign_out(char *username) {
  char temp_string[BUFFER_SIZE];

  printf("\n\nSIGNING OUT\n-----------\n");
  printf("Enter username: ");
  fgets(temp_string, BUFFER_SIZE, stdin);
  temp_string[strlen(temp_string) - 1] = '\0';

  if (strcmp(username, temp_string)){
    printf("\n\nUsername not match.\n");
    return SIGNED_IN;
  }

  printf("\n\nGoodbye %s\n", username);
  strcpy(username,"");
  return NOT_SIGNED_IN;
}


/*
 * Function 7: Homepage with domain name
 * */
void display_homepage_domain(account root, char *username){
  printf("\n\nHOMEPAGE\n--------------\n");

  account temp = find_by_username(root, username);
  printf(get_domain_name(temp->homepage));
}


/*
 * Function 8: Homepage with IP address
 * */
void display_homepage_ip(account root, char *username){
  printf("\n\nHOMEPAGE\n--------------\n");

  account temp = find_by_username(root, username);
  printf(get_ip_address(temp->homepage));
}
