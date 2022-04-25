#include "../../includes/builtins.h"

int	env(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
