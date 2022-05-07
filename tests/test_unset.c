#include "../includes/builtins.h"

int main(int argc, char *argv[], char *envp[])
{
	t_command *cmd;

	cmd = init_builtins(envp);
	cmd->argv = argv;

	if (builtins_export(cmd))
		return (1);
	if (builtins_unset(cmd))
		return (1);
	// Emulate child process result
	char *token;
	char *delim = "=";
	token = strtok(cmd->argv[1], delim);
	printf("%s", ms_getenv(cmd->envp, token));
	printf("\n");
	return (0);
}
