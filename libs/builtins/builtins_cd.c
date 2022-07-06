/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:26:00 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/05 22:38:54 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	_builtins_cd(t_command *cmd, char *buf)
{
	if (cmd->argc == 1)
	{
		cd_home(cmd->envp);
		set_oldpwd(cmd->envp, buf);
		return (1);
	}
	if (cmd->argc > 2)
	{
		print_err_msg(cmd->argv[0], "too many arguments");
		cmd->status = 127;
		return (1);
	}
	if (cmd->argv[1][0] == '-')
	{
		chdir(ms_getenv(cmd->envp, "OLDPWD"));
		set_oldpwd(cmd->envp, buf);
		return (1);
	}
	return (0);
}

int	builtins_cd(t_command *cmd)
{
	char	buf[1025];
	int		status;

	status = 0;
	getcwd(buf, 1024);
	if (_builtins_cd(cmd, buf))
		return (0);
	status = cd(cmd->argv, cmd->envp);
	if (status == 0)
		return (set_oldpwd(cmd->envp, buf));
	return (status);
}
