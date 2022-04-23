#include "../../includes/builtins.h"

static int	first_char_is_equal(const char *first)
{
	if (ft_strncmp(first, "=", 1) == 0)
		return (1);
	return (0);
}

static int	has_equals(const char *first)
{
	if (ft_strchr(first, '=') != NULL)
		return (1);
	return (0);
}

static int	print_export_err(const char *arg, int errnum)
{
	printf("bash: export: `%s': not a valid identifier\n", arg);
	return (errnum);
}

static int	handle_key_value(t_command *cmd)
{
	if (cmd->argv[1] == NULL)
		return (export(cmd->argv[0], cmd->envp));
	return (print_export_err(cmd->argv[1], 1));
}

int	builtins_export(t_command *cmd)
{
	if (has_equals(cmd->argv[0]))
		return (handle_key_value(cmd));
	if (first_char_is_equal(cmd->argv[1]))
		return (print_export_err(cmd->argv[1], 1));
	if (!has_equals(cmd->argv[1]) && has_equals(cmd->argv[2]))
		return (print_export_err(cmd->argv[2], 2));
	if (has_equals(cmd->argv[1]))
		return (export(cmd->argv[1], cmd->envp));
	perror("Unknown error");
	return (-1);
}
