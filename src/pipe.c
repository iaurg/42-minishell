/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:41:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/04 20:25:06 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	move_fds_to_next_pipe(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

static int	no_next_pipe(char *arg)
{
	signal(SIGINT, newline_hook);
	if (!arg)
		return (1);
	return (0);
}

static int	skip_pipe_arg(char *arg, int i)
{
	if (!arg)
		return (i);
	return (i + 1);
}

static int	handle_pipes(int *fds, t_command *cmd)
{
	int		son_count;
	int		*flag;
	int		i;
	int		j;

	son_count = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	j = 0;
	while (cmd->argv[j])
	{
		i = 0;
		while (cmd->argv[j + i] && ft_memcmp(cmd->argv[j + i], "|", 2))
			i++;
		flag[1] = no_next_pipe(cmd->argv[i + j]);
		execute_pipe(flag, fds, cmd, j);
		son_count++;
		flag[0] = 0;
		move_fds_to_next_pipe(fds);
		j += skip_pipe_arg(cmd->argv[j + i], i);
	}
	free(flag);
	return (son_count);
}

int	handle_execute(t_command *cmd)
{
	int		fds[4];
	int		pipe_stdin;
	int		son_count;
	int		i;

	pipe_stdin = dup(STDIN_FILENO);
	i = 0;
	while (cmd->argv[i] && (ft_strncmp(cmd->argv[i], "|", 2) != 0))
		i++;
	if (!cmd->argv[i])
		return (execute(cmd));
	pipe(fds);
	pipe(fds + 2);
	son_count = handle_pipes(fds, cmd);
	while (son_count-- > 0)
		wait(&cmd->status);
	i = -1;
	while (++i < 4)
		close(fds[i]);
	dup2(pipe_stdin, STDIN_FILENO);
	cmd->status = cmd->status % 256;
	return (1);
}
