# include "validator.h"
# include "resolver.h"

int main(int argc, char **argv) {
  if (argc != 3 || (strcmp(argv[1], "1") && strcmp(argv[1], "2"))) {
    printf("Wrong parameter: Must have 2 arguments");
    return 0;
  }
  
  int func = atoi(argv[1]);
  char *result;

  switch (func) {
    case 1:
      result = get_host_by_addr(argv[2]);
      printf("%s", result);
      break;

    case 2:
      result = get_host_by_name(argv[2]);
      printf("%s", result);
      break;
  }

  return 0;
}
