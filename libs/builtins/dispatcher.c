#include "../../includes/builtins.h"

static t_dispatcher *run_cmd(t_builtin number)
{
	static t_dispatcher	*execute[SIZE];

	execute[EXPORT] = builtins_export;
	execute[PWD] = builtins_pwd;
	execute[ECHO] = builtins_echo;

	return (execute[number]);
}

int run(t_command *cmd)
{
	int	status;
	t_dispatcher *run;

	run = run_cmd(cmd->builtin);
	status = (*run)(cmd);

	return (status);
}
