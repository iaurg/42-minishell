#include "../includes/builtins.h"

int main(int argc, char *argv[], char *envp[])
{
	t_command *cmd;

	cmd = init_builtins(envp);
	cmd->argv = argv;

	if (builtins_export(cmd))
		return (1);
	// Emulate child process result
	char *token = ft_strtok(argv[1], "=");
	char *tmp = ms_getenv(cmd->envp, token);
	if (tmp == NULL)
		return (1);
	printf("%s\n", tmp);

	return (0);
}
