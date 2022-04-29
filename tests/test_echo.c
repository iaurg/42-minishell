#include "../includes/builtins.h"

int	main(int argc, char *argv[], char *envp[])
{
	int i = argc;
	//	Strange behavior when testing only with echo, with no params or flags

	t_command cmd;

	cmd = (t_command) {
		.argc = argc,
		.argv = ++argv,
		.envp = envp
	};
	builtins_echo(&cmd);
	return (i);
}
