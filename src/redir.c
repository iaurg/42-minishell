/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 07:02:18 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/09 09:35:26 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_redirection(t_command *cmd, int i, int fd)
{
	int		status;
	char	c;

	while (cmd->argv[i])
	{
		if (!ft_memcmp(cmd->argv[i], ">", 2))
			fd = open(cmd->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_memcmp(cmd->argv[i], ">>", 3))
		{
			fd = open(cmd->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
			status = read(fd, &c, 1);
			while (status)
				status = read(fd, &c, 1);
		}
		i++;
		if (cmd->argv[i]
			&& (!ft_memcmp(cmd->argv[i], ">>", 3)
				|| !ft_memcmp(cmd->argv[i], ">", 2)))
			close(fd);
	}
	return (fd);
}

int	set_fd(t_command *cmd)
{
	int		i;
	int		fd;

	i = 0;
	fd = STDOUT_FILENO;
	if (!cmd->argv[i])
		return (1);
	while (cmd->argv[i] && ft_memcmp(cmd->argv[i], ">", 2)
		&& ft_memcmp(cmd->argv[i], ">>", 3))
		i++;
	if (!cmd->argv[i])
	{
		cmd->fd = fd;
		return (0);
	}
	cmd->fd = read_redirection(cmd, i, fd);
	return (0);
}

static int	count_redir(t_command *cmd)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < cmd->argc)
	{
		if (ft_strncmp(cmd->argv[i], ">", 1) == 0
			|| ft_strncmp(cmd->argv[i], ">>", 2) == 0)
		{
			count++;
			i++;
		}
	}
	return (count * 2);
}

static int	remove_redirect_args(t_command *cmd)
{
	int		i;
	int		j;
	char	**args;

	cmd->argc -= count_redir(cmd);
	args = (char **)ft_calloc(sizeof(char *), cmd->argc + 1);
	i = 0;
	j = 0;
	while (j < cmd->argc)
	{
		if (!ft_memcmp(cmd->argv[i], ">", 2)
			|| !ft_memcmp(cmd->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(cmd->argv[i++]);
	}
	free_matrix(cmd->argv);
	cmd->argv = args;
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	if (set_fd(cmd))
	{
		write(STDERR_FILENO, "Unexpected error while setting fd\n", 35);
		return (1);
	}
	if (remove_redirect_args(cmd))
	{
		write(STDERR_FILENO,
			"Unexpected error while removing redirection args\n", 46);
		return (1);
	}
	return (0);
}
