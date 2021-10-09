# include <stdio.h>
# include <stdlib.h>
# include "utils.h"

void wait_for_enter() {
  printf("\nPress [Enter] key to continue\n");
  while (getchar() != '\n');
  getchar();
}


void print_menu() {
    system("clear");
    printf("USER MANAGEMENT PROGRAM\n--------------------------\n");
    printf("1. Register\n");
    printf("2. Activate\n");
    printf("3. Sign in\n");
    printf("4. Search\n");
    printf("5. Change password\n");
    printf("6. Sign out\n");
    printf("Your choice (1-6, other to quit): ");
}


