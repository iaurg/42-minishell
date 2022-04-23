#include "../../includes/builtins.h"

int	export(char *arg, char *envp[])
{
	unsigned int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = ft_strdup(arg);
	envp[i + 1] = NULL;
	return (0);
}
