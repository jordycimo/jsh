#include <stdlib.h>
#include <stdio.h>

/* compile time config */
const bool echo = true;

char* input(char* line) {
  size_t len = 0;
  ssize_t read;

  read = getline(&line, &len, stdin);

  if (read != -1) {
    if (echo) {
      printf("%s", line);
    }
  } else {
    printf("error taking input");
  }

  return line;
}



int main(int argc, char *argv[]) {
  char *line = NULL;

  /* prompt */
  printf("> ");

  /* get input into 'line' */
  line = input(line);

  free(line);
  return 0;
}
