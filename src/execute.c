/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:19 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/10 09:25:40 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_builtin	translate_builtin(char *name)
{
	if (ft_strncmp(name, "cd", 2) == 0)
		return (CD);
	if (ft_strncmp(name, "env", 3) == 0)
		return (ENV);
	if (ft_strncmp(name, "echo", 4) == 0)
		return (ECHO);
	if (ft_strncmp(name, "export", 6) == 0
		|| (ft_strchr(name, '=') != NULL))
		return (BUILTINS_EXPORT);
	if (ft_strncmp(name, "unset", 5) == 0)
		return (UNSET);
	if (ft_strncmp(name, "exit", 4) == 0)
		return (EXIT);
	return (SIZE);
}

static int	try_builtins_exec(t_command *cmd)
{
	int			status;

	status = 1;
	cmd->builtin = translate_builtin(cmd->argv[0]);
	status = run(cmd);
	cmd->status = status;
	return (status);
}

int	execute(t_command *cmd)
{
	if (!cmd->argv[0])
		return (1);
	if (handle_redirections(cmd))
		return (0);
	if (try_builtins_exec(cmd) == 0)
		return (1);
	return (system_exec(cmd));
}
