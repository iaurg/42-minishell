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

  for (i = 0; i < MAX_CMDS; i++)
  {
    parsed[i] = strsep(&string, " ");

    if (parsed[i] == NULL)
      break;
    if (strlen(parsed[i]) == 0)
      i--;
  }
}

void open_help()
{
  puts("\n***WELCOME TO MY SHELL HELP***"
       "\nList of Commands supported:"
       "\n>cd"
       "\n>ls"
       "\n>exit"
       "\n>all other general commands available in UNIX shell"
       "\n>pipe handling"
       "\n>improper space handling");
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
    if (strcmp(parsed[0], commands_list[i]) == 0)
    {
      switch_own_arg = i + 1;
      break;
    }
    i++;
  }

  switch (switch_own_arg)
  {
  case 1:
    printf("Goodbye!\n");
    exit(0);
  case 2:
    chdir(parsed[1]);
    return (1);
  case 3:
    open_help();
    return (1);
  case 4:
    username = getenv("USER");
    printf("\nHello %s.\nMind that this is "
           "not a place to play around."
           "\nUse help to know more..\n",
           username);
    return (1);
  default:
    break;
  }
  return (0);
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

void exec_args(char **parsed_args)
{
  pid_t pid = fork();

  if (pid == -1)
    printf("Failed to fork...\n");
  else if (pid == 0)
  {
    if (execvp(parsed_args[0], parsed_args) < 0)
      printf("Command could not be executed \n");
    exit(0);
  }
  else
  {
    wait(NULL);
    return;
  }
}

void exec_args_piped(char **parsed, char **parsed_args_piped)
{
  // 0 read, 1 write
  int pipefd[2];
  pid_t p1, p2;

  if (pipe(pipefd) < 0)
  {
    printf("\nPipe could not be initialized");
    return;
  }
  p1 = fork();
  if (p1 < 0)
  {
    printf("\nCould not fork");
    return;
  }

  if (p1 == 0)
  {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    if (execvp(parsed[0], parsed) == 0)
    {
      printf("\nCould not execute command 1...");
      exit(0);
    }
  }
  else
  {
    p2 = fork();

    // Failed fork
    if (p2 < 0)
    {
      printf("\n Could not fork");
      return;
    }

    if (p2 == 0)
    {
      close(pipefd[1]);
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[0]);
      if (execvp(parsed_args_piped[0], parsed_args_piped) < 0)
      {
        printf("\nCould not execute command 2..");
        exit(0);
      }
    }
    else
    {
      wait(NULL);
      wait(NULL);
    }
  }
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
    // print_dir();
    if (take_input(input_string))
      continue;
    exec_flag = process_string(input_string, parsed_args, parsed_args_piped);

    if (exec_flag == 1)
      exec_args(parsed_args);
    if (exec_flag == 2)
      exec_args_piped(parsed_args, parsed_args_piped);
  }
  return (0);
}