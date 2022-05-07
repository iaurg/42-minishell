#include "../includes/builtins.h"

int	main(int argc, char *argv[], char *envp[])
{
	int i = argc;
	//	Strange behavior when testing only with echo, with no params or flags

	t_command *cmd;

	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_echo(cmd);
	return (i);
}
