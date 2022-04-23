#include "../includes/builtins.h"

int main(int argc, char *argv[], char *envp[])
{
	t_command cmd;

	// Test setup to emulate argv[1] as argv[0]
	cmd = (t_command) {
		.argc = argc,
		.argv = ++argv,
		.envp = envp
	};

	if (builtins_export(&cmd))
		return (1);

	// Emulate child process result
	char *token;
	char *delim = "=";
	token = strtok(cmd.argv[0], delim);
	printf(getenv(token));
	printf("\n");
	return (0);
}
