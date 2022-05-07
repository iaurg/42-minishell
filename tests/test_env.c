#include "../includes/builtins.h"

int main(int argc, char *argv[], char *envp[])
{
	t_command *cmd;

	cmd = init_builtins(envp);
	cmd->argv = argv;
	builtins_env(cmd);
	return (0);
}
