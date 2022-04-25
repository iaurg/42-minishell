#include "../../includes/builtins.h"

int builtins_echo(t_command *cmd)
{
	if (cmd->argc <= 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	echo(cmd->argv, 1);
	return (0);
}

int builtins_env(t_command *cmd)
{
	printf("env! %s\n", cmd->argv[0]);
	env();
	return (0);
}
