#include "../../includes/builtins.h"

int	builtins_export(t_command *cmd)
{
	printf("export!\n");
	return (0);
}

int builtins_echo(t_command *cmd)
{
	printf("echo!\n");
	return (0);
}
