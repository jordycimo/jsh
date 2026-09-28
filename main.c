#include <stdlib.h>
#include <stdio.h>

/* compile time config */
const bool echo = true;

// takes input and returns line, returns char array.
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

char* tokenize(char* line) {

}

// main loop.
/*
take input
tokenize
run command with arguments
loop
*/
int main(int argc, char *argv[]) {
  char *line = NULL;

  /* prompt */
  printf("> ");

  /* get input into 'line' */
  line = input(line);

  /* lets split this into tokens */
  tokenize(line);

  free(line);
  return 0;
}
