#include "../../includes/builtins.h"

int builtins_echo(t_command *cmd)
{
	printf("echo!\n");
	return (0);
}

int builtins_env(t_command *cmd)
{
	env(cmd->envp);
	return (0);
}
