#include "../includes/minishell.h"

int init_shell()
{
  char *username;
  clear();
  printf("Hello minishellson\n");
  username = getenv("USER");
  printf("USER: %s \n", username);
  sleep(1);
  clear();
}

int main(void)
{
  char input_string[BUFFERSIZE];
  char *parsed_args[MAX_CMDS];
  char *parsed_args_piped[MAX_CMDS];
  int exec_flag;

  exec_flag = 0;
  init_shell();
  return (0);
}