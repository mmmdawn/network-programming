#include "utils.h"
#include "functions.h"

int main(int argc, char **argv) {
  int pos;
  char key = '1';
  char username[LOGIN_INFO_SIZE];
  char password[LOGIN_INFO_SIZE];
  char temp_string[LOGIN_INFO_SIZE];

  char session_status = NOT_SIGNED_IN;
  char *attemps = (char*)calloc(BUFFER_SIZE, LOGIN_INFO_SIZE);

  char **usernames = (char**)malloc(BUFFER_SIZE * sizeof(char*));
  for ( int i = 0; i < BUFFER_SIZE; ++i ) {
    usernames[i] = (char*)calloc(LOGIN_INFO_SIZE, sizeof(char));
  }
    

  account root = load_file();

  while (key > '0' && key < '7') {
    print_menu();
    scanf("%c", &key);

    switch (key) {
      case '1':
        if (session_status == SIGNED_IN) {
          printf("\n\nPlease sign out first.\n");
          wait_for_enter();
          break;
        }

        root = create_account(root);
        wait_for_enter();
        break;
      case '2':
        printf("\nACTIVATING ACCOUNT\n-----------\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        printf("Code: ");
        scanf("%s", temp_string);

        root = activate_account(root, username, password, temp_string);
        wait_for_enter();
        break;
      case '3':
        if (session_status == SIGNED_IN)
          printf("\n\nAlready signed in.\n");
        else 
          session_status = sign_in(root, usernames, attemps, &pos);

        wait_for_enter();
        break;
      case '4':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else {
          printf("\n\nSEARCH\n-----------\n");
          printf("Username: ");
          scanf("%s", username);
          search(root, username);
        }
        wait_for_enter();
        break;
      case '5':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else {
          root = change_password(root, usernames[pos]);
        }

        wait_for_enter();
        break;
      case '6':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nAccount is not signed in.\n");

        } else {
          printf("\n\nSIGNING OUT\n-----------\n");
          printf("Enter username: ");
          scanf("%s", username);
          if (strcmp(username, usernames[pos])){
            printf("\n\nUsername not match.\n");

          } else {
            printf("\n\nGoodbye %s\n", usernames[pos]);
            session_status = NOT_SIGNED_IN;
            pos = -1;
          }
        }
        wait_for_enter();
        break;
      default:
        printf("\n\nGOOD BYE!\n");
    }
  }
  
  free(usernames);
  free(attemps);
  return 0;
}
