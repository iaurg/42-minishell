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

void print_dir()
{
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("\ndir: %s", cwd);
}

int take_input(char *input_text)
{
  char *buffer;

  buffer = readline("\n>>>");
  if (strlen(buffer) != 0)
  {
    add_history(buffer);
    strcpy(input_text, buffer);
    return (0);
  }
  else
  {
    return (1);
  }
}

int parse_pipe(char *string, char **string_piped)
{
  int i;

  i = 0;
  while (i < 2)
  {
    string_piped[i] = strsep(&string, "|");
    if (string_piped[i] == NULL)
      break;
    i++;
  }

  if (string_piped[1] == NULL)
    return (0);
  else
    return (1);
}

void parse_space(char *string, char **parsed)
{
  int i;

  i = 0;
  while (i < MAX_CMDS)
  {
    parsed[i] = strsep(&string, " ");
    if (parsed[i] == NULL)
      break;
    i++;
    if (strlen(parsed[i]) == 0)
      i--;
  }
}

int own_cmd_handler(char **parsed)
{
  int nbr_own_commands;
  nbr_own_commands = 4;

  int i;
  int switch_own_arg;
  char *commands_list[nbr_own_commands];
  char *username;

  i = 0;
  switch_own_arg = 0;
  commands_list[0] = "exit";
  commands_list[1] = "cd";
  commands_list[2] = "help";
  commands_list[3] = "hello";

  while (i < nbr_own_commands)
  {

    i++;
  }
}

int process_string(char *string, char **parsed_args, char **parsed_args_piped)
{
  char *string_piped[2];
  int piped;
  piped = 0;

  piped = parse_pipe(string, string_piped);

  if (piped)
  {
    parse_space(string_piped[0], parsed_args);
    parse_space(string_piped[1], parsed_args_piped);
  }
  else
  {
    parse_space(string, parsed_args);
  }

  if (own_cmd_handler(parsed_args))
    return (0);
  else
    return (1 + piped);
}

int main(void)
{
  char input_string[BUFFERSIZE];
  char *parsed_args[MAX_CMDS];
  char *parsed_args_piped[MAX_CMDS];
  int exec_flag;

  exec_flag = 0;
  init_shell();
  while (1)
  {
    print_dir();
    if (take_input(input_string))
      continue;
    exec_flag = process_string(input_string, parsed_args, parsed_args_piped);
  }
  return (0);
}