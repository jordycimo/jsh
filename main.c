#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  /* get input into 'line' */
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  printf("> ");

  read = getline(&line, &len, stdin);

  if (read != -1) {
    printf("%s", line);
  } else {
    printf("error taking input");
  }

  free(line);
  return 0;
}
