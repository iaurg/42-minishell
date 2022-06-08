/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/07 18:18:50 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_first_arg(t_command *cmd, int first_arg_pos)
{
	int		i;
	char	**tmp;

	i = 0;
	while (cmd->argv[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i - first_arg_pos));
	i = 0;
	while (cmd->argv[i + first_arg_pos])
	{
		tmp[i] = ft_strdup(cmd->argv[i + first_arg_pos]);
		i++;
	}
	free_matrix(cmd->argv);
	cmd->argv = tmp;
	cmd->argc = i;
}

int	command_comes_first(t_command *cmd)
{
	if (cmd->argc <= 1)
		return (0);
	if (cmd->argv[1][0] == '<' && cmd->argv[1][1] == '\0'
		&& cmd->argv[2] && cmd->argc == 3)
	{
		read_file(cmd->argv[2]);
		free(cmd->argv[1]);
		cmd->argv[1] = cmd->argv[2];
		cmd->argc--;
		cmd->argv[2] = NULL;
		return (1);
	}
	return (0);
}

int	handle_first_arg(t_command *cmd)
{
	int		first_arg_pos;
	char	*filename;

	first_arg_pos = 0;
	if (command_comes_first(cmd))
		return (0);
	if (cmd->argv[0][0] == '<' && cmd->argv[0][1] == '<')
		return (0);
	filename = ft_strchr(cmd->argv[0], '<');
	if (filename)
	{
		filename++;
		first_arg_pos++;
		if (*filename == '\0')
			filename = cmd->argv[first_arg_pos++];
		read_file(filename);
		clear_first_arg(cmd, first_arg_pos);
	}
	return (0);
}

void	execute_child_command(t_command *cmd)
{
	char	*abspath;
	char	**compat_envp;

	handle_first_arg(cmd);
	abspath = solve_absolute_path(cmd);
	compat_envp = to_array(cmd->envp);
	execve(abspath, cmd->argv, compat_envp);
	free_matrix(compat_envp);
	if (abspath != NULL)
		free(abspath);
}

int	system_exec(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, child_signal_handler);
	if (pid == 0)
	{
		execute_child_command(cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		return (0);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		if (status > 0)
			cmd->status = 127;
		else
			cmd->status = 0;
	}
	return (1);
}
