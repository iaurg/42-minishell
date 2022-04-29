#include "../includes/builtins.h"

int main(int argc, char *argv[], char *envp[])
{
	t_command cmd;

	cmd = (t_command) {
		.argc = argc,
		.argv = argv,
		.envp = envp
	};

	builtins_env(&cmd);
	return (0);
}
