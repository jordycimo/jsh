#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>

/* get input and return line, if this fails, return an error */
char* input(char* line) {
  size_t len = 0;
  ssize_t read;

  /* get input from stdin and store in line, read holds the return value */
  read = getline(&line, &len, stdin);

  if (read != -1) {
    line[strlen(line)-1] = '\0';
    return line;
  } else {
    return "error taking input!";
  }
}

/* split input into tokens and return the array of tokens */
int tokenize(char* line, char* command, char* args[]) {
  char* token = strtok(line, " ");
  int i = 0;

  /* turns input into null-terminated tokens */
  while (token != NULL) {
    args[i++] = token;
    token = strtok(NULL, " ");
  }
  args[i] = NULL;

  /* copy first argument to command */
  if (args[0]) {
    strcpy(command, args[0]);
  } else {
    printf("\n");
  }

  /* if command isnt NULL, return success */
  if (command) {
    return 0;
  } else {
    return 1;
  }
}

/* execute command with args and wait to return */
int execute(char* command, char* args[]) {
  pid_t pid = fork();
  int status;

  if (pid < 0) {
    /* error */
    printf("error forking!");
  } else if (pid == 0) {
    /* child process */
    if(execvp(command, args) == -1) {
      printf("unknown command");
    }
    exit(EXIT_FAILURE);
    return -1;
  } else {
    /* parent process */
    waitpid(pid, &status, 0);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char* line = NULL;

  char command[512];
  char* args[64];

  bool running = true;
  bool echo = false;

  while (running) {
    /* prompt */
    printf("> ");

    /* get input from stdin, auto removes newline*/
    line = input(line);

    /* tokenize input, seperate command and args */
    if(tokenize(line, command, args) != 0) {
      printf("error tokenizing!");
    }

    /* check builtins */
    if (strcmp(command, "exit") == 0) {
      running = false;
      continue;
    }

    if (echo) {
      /* print command and its args*/
      printf("%s", command);

      for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
      }
    }

    /* free line, we dont use it again */
    free(line);

    /* execute command with args */
    execute(command, args);
  }

    /* newline for look good */
    printf("\n");
  return 0;
}
