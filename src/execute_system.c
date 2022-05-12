/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/12 02:43:39 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		fprintf(stderr, "bash: no such file or directory: %s\n", filename);
		return ;
	}
	dup2(fd, 0);
	close(fd);
}

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

int	handle_first_arg(t_command *cmd)
{
	int		first_arg_pos;
	char	*filename;
	char	tmp[2];

	first_arg_pos = 0;
	if (cmd->argv[0][0] == '<' && cmd->argv[0][1] == '<')
		return (0);
	if (ft_isdigit(cmd->argv[0][0]) && cmd->argv[0][1] == '<')
	{
		tmp[0] = cmd->argv[0][0];
		tmp[1] = '\0';
		cmd->fd = ft_atoi(tmp);
	}
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
	compat_envp = to_array(cmd->envp);
	abspath = solve_absolute_path(cmd);
	if (execve(abspath, cmd->argv, compat_envp) == -1)
		perror("Command not found");
	free(compat_envp);
	free(abspath);
}

int	system_exec(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
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
