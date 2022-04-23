#include "../../includes/builtins.h"

int builtins_echo(t_command *cmd)
{
	printf("echo!\n");
	return (0);
}

int builtins_env(t_command *cmd)
{
	env();
	return (0);
}

int builtins_cd(t_command *cmd)
{
	printf("cd!\n");
	return (0);
}
