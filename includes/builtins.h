#ifndef BUILTINS_H

# define BUILTINS_H
# define MAX_ARGS 256

#include <unistd.h>
#include <stdio.h>

typedef enum builtin {
	PWD, ECHO, CD, EXPORT, SIZE
} t_builtin;

typedef struct s_command {
	int argc;
	char *argv[MAX_ARGS];
	t_builtin	builtin;
} t_command;

typedef int	t_dispatcher(t_command *cmd);

/* internal functions */
int			pwd(void);

/* public interface */
int builtins_echo(t_command *cmd);
int builtins_pwd(t_command *cmd);
int builtins_export(t_command *cmd);

/* executors */

int run(t_command *cmd);


#endif
