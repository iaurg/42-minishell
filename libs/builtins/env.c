#include "../../includes/builtins.h"

int	env(void)
{
	int	i;

	i = -1;
	while (__environ[++i])
	{
		write(STDOUT_FILENO, __environ[i], ft_strlen(__environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
