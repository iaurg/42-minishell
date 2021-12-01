#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MAX_LINE = 1024;
char *prompt = "iaurgsh> ";

void eval(char *cmdline)
{
  int bg;
  struct command cmd;

  printf("Evaluating '%s' \n", cmdline);

  bg = parse()
}

int main(void)
{
  char cmdline[MAX_LINE];

  while (1)
  {
    printf("%s", prompt);

    // getting string from stdin
    if (fgets(cmdline, MAX_LINE, stdin) == NULL && ferror(stdin))
      error("fgets errorr");

    if (feof(stdin))
    {
      printf("\n");
      exit(0);
    }

    cmdline[strlen(cmdline) - 1] = '\0';

    eval(cmdline);
  }
}