#include "../../includes/builtins.h"

static int	builtins_none(t_command *cmd)
{
	(void)cmd;
	return (1);
}

static t_dispatcher *run_cmd(t_builtin number)
{
	static t_dispatcher	*table[SIZE];

	table[BUILTINS_EXPORT] = builtins_export;
	table[ENV] = builtins_env;
	table[ECHO] = builtins_echo;
	table[CD] = builtins_cd;
	table[EXIT] = builtins_exit;
	table[UNSET] = builtins_unset;
	table[SIZE] = builtins_none;
	return (table[number]);
}

int run(t_command *cmd)
{
	int				status;
	t_dispatcher	*run;

	run = run_cmd(cmd->builtin);
	status = (*run)(cmd);
	return (status);
}
