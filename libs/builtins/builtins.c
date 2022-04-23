#include "../../includes/builtins.h"

int builtins_echo(t_command *cmd)
{
	printf("echo! %s\n", cmd->argv[0]);
	return (0);
}

int builtins_env(t_command *cmd)
{
	printf("env! %s\n", cmd->argv[0]);
	env();
	return (0);
}
