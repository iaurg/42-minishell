/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:02:52 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/19 18:44:45 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	print_export_err(const char *arg, int errnum)
{
	fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", arg);
	return (errnum);
}

static int	handle_key_value(t_command *cmd)
{
	if (cmd->argv[1] == NULL)
		return (export(cmd->argv[0], cmd->envp));
	return (print_export_err(cmd->argv[1], 1));
}

static void	print_envp(t_command *cmd)
{
	t_list	*temp;

	temp = *cmd->envp;
	while (temp->next != NULL)
	{
		ft_putstr_fd(temp->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = temp->next;
	}
	return ;
}

static int	export_key_value_in_arg_zero(t_command *cmd)
{
	if (ft_strchr(cmd->argv[0], '=') != NULL)
	{
		export(cmd->argv[0], cmd->envp);
		return (1);
	}
	if (cmd->argv[1] == NULL)
	{
		print_envp(cmd);
	}
	return (0);
}

int	builtins_export(t_command *cmd)
{
	char	*tmp;
	int		status;

	if (export_key_value_in_arg_zero(cmd) || cmd->argv[1] == NULL)
		return (0);
	if (has_equals(cmd->argv[0]))
		return (handle_key_value(cmd));
	if (first_char_is_equal(cmd->argv[1]))
		return (print_export_err(cmd->argv[1], 1));
	if ((!has_equals(cmd->argv[1])) && (cmd->argv[2] == NULL))
	{
		tmp = ft_strjoin(cmd->argv[1], "=");
		status = export(tmp, cmd->envp);
		free(tmp);
		return (status);
	}
	if ((!has_equals(cmd->argv[1])) && (has_equals(cmd->argv[2])))
		return (print_export_err(cmd->argv[2], 1));
	if (has_equals(cmd->argv[1]))
		return (export(cmd->argv[1], cmd->envp));
	if (cmd->argv[1] == NULL)
		return (env(cmd->envp, cmd->fd));
	perror("Unknown error");
	return (-1);
}
