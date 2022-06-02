/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:23:50 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 22:25:56 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtins_echo(t_command *cmd)
{
	if (cmd->argc <= 1)
	{
		write(cmd->fd, "\n", 1);
		return (0);
	}
	echo(cmd->argv, cmd->fd);
	return (0);
}

int	builtins_env(t_command *cmd)
{
	env(cmd->envp, cmd->fd);
	return (0);
}

int	builtins_exit(t_command *cmd)
{
	if (cmd->argc > 1)
		exit(ft_atoi(cmd->argv[1]));
	else
		exit(0);
	return (0);
}

int	builtins_unset(t_command *cmd)
{
	size_t	size;

	size = 0;
	while (cmd->argv[size])
		size++;
	unset(&cmd->argv[1], cmd->envp, size - 1);
	return (0);
}
