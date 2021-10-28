#include "functions.h"

int main(int argc, char **argv) {
  char key = '1';
  char session_status = NOT_SIGNED_IN;
  char username[LOGIN_INFO_LEN];

  account root = load_file();

  while (key > '0' && key < '9') {
    print_menu();
    scanf("%c", &key);
    clear_buffer();

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
        root = activate_account(root);
        wait_for_enter();
        break;

      case '3':
        if (session_status == SIGNED_IN)
          printf("\n\nAlready signed in.\n");
        else 
          session_status = sign_in(root, username);

        wait_for_enter();
        break;

      case '4':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else search(root);

        wait_for_enter();
        break;

      case '5':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else {
          root = change_password(root, username);
        }

        wait_for_enter();
        break;

      case '6':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else session_status = sign_out(username);

        wait_for_enter();
        break;
      case '7':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else display_homepage_domain(root, username);

        wait_for_enter();
        break;
      case '8':
        if (session_status == NOT_SIGNED_IN) {
          printf("\n\nPlease sign in first.\n");
        } else display_homepage_ip(root, username);

        wait_for_enter();
        break;
      default:
        printf("\n\nGOOD BYE!\n");
    }
  }
  
  return 0;
}
