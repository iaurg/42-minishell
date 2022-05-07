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
	env(cmd->envp);
	return (0);
}

int	builtins_cd(t_command *cmd)
{
	return (0);
}

int	builtins_exit(t_command *cmd)
{
	return (0);
}

int	builtins_unset(t_command *cmd)
{
	unset(cmd->envp, cmd->argv);

	return (0);
}
