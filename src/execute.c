/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:19 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/07 05:35:37 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

//static t_command	*get_command(void)
//{
//	static t_command	*cmd;

//	if (!cmd)
//		cmd = (t_command *)malloc(sizeof(t_command));
//	return (cmd);
//}

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

static void	refresh_builtins(t_command *cmd)
{
	int	argc;

	argc = 0;
	while (cmd->argv[argc])
		argc++;
	cmd->argc = argc;
	cmd->builtin = translate_builtin(cmd->argv[0]);
}

static int	try_builtins_exec(t_command *cmd)
{
	int			status;

	status = 1;
	refresh_builtins(cmd);
	status = run(cmd);
	return (status);
}

int	execute(t_command *cmd)
{
	pid_t		pid;
	int			status;

	if (!cmd->argv[0])
		return (1);
	if (try_builtins_exec(cmd) == 0)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execvp(cmd->argv[0], cmd->argv) == -1)
			perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		return (0);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
