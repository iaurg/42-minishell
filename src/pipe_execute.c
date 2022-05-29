/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:41:49 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/28 21:56:43 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	newline_hook(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
}

static void	define_child_args(t_command *cmd, int i)
{
	char	**aux;
	int		j;
	int		k;

	j = 0;
	while (cmd->argv[i + j] && ft_memcmp(cmd->argv[i + j], "|", 2))
		j++;
	aux = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		aux[k] = ft_strdup(cmd->argv[i + k]);
	cmd->argv = aux;
	cmd->argc = j;
}

void	execute_pipe(int *flag, int *fds, t_command *cmd, int pos)
{
	int		i;
	int		origin_argc;
	char	**origin_argv;

	signal(SIGINT, newline_hook);
	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], STDIN_FILENO);
		if (!flag[1])
			dup2(fds[3], STDOUT_FILENO);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		origin_argc = cmd->argc;
		origin_argv = cmd->argv;
		define_child_args(cmd, pos);
		execute(cmd);
		free_matrix(cmd->argv);
		cmd->argc = origin_argc;
		cmd->argv = origin_argv;
		exit(cmd->status);
	}
}
