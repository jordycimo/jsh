#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* get input and return line, if this fails, return an error */
char* input(char* line) {
  size_t len = 0;
  ssize_t read;

  /* get input from stdin and store in line, read holds the return value */
  read = getline(&line, &len, stdin);

  if (read != -1) {
    return line;
  } else {
    return "error taking input!";
  }
}

/* split input into tokens and return the array of tokens */
char* tokenize(char* line, char* command, char** args) {
  char* token = strtok(line, " ");
  int i = 0;

  while (token != NULL) {
    args[i++] = token;
    token = strtok(NULL, " ");
  }
  args[i] = NULL;

  /* copy first argument to command */
  strcpy(command, args[0]);
}

int main(int argc, char *argv[]) {
  char* line = NULL;

  char command[512];
  char* args[64];

  /* prompt */
  printf(">");

  /* get input from stdin, auto removes newline*/
  line = input(line);

  /* tokenize input, seperate command and args */
  tokenize(line, command, args);

  /* free line, we dont use it again */
  free(line);

  /* print each character and signify any null bytes */
  for (int i = 0; command[i]; i++) {
      printf("%c", command[i]);
  }

  for (int i = 0; args[i]; i++) {
    printf("\n");
    for (int j = 0; args[j]; j++) {
      printf("%c ", args[i][j]);
    }
  }

  return 0;
}
