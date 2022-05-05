#include "minunit.h"
#include "../includes/builtins.h"

int main(void)
{
	int status;
	t_command cmd;

	cmd = (t_command) {
		.builtin = BUILTINS_EXPORT,
		.argc = 0,
		.argv = NULL,
	};

	status = run(&cmd);

	cmd.builtin = PWD;
	status = run(&cmd);
	cmd.builtin = ECHO;
	status = run(&cmd);

	return (status);
}
