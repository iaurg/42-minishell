#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFERSIZE 1024
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MAX_CMDS 100
# define clear() printf("\033[H\033[J") // global function

# endif