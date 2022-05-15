/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 06:43:18 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/15 06:45:16 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libs/get_next_line/get_next_line.h"

void	parse_here_doc(char *delim, int *fd)
{
	char	*line;
	int		i;

	close(fd[READ_END]);
	signal(SIGINT, handle_heredoc_signal);
	ft_putstr_fd("… ", STDIN_FILENO);
	i = get_next_line(STDIN_FILENO, &line);
	while (i)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1)
			|| *(get_signal_triggered_status()) == 1)
		{
			close(fd[WRITE_END]);
			free(line);
			return ;
		}
		ft_putstr_fd(ft_strjoin(line, "\n"), fd[WRITE_END]);
		free(line);
		ft_putstr_fd("… ", STDIN_FILENO);
		i = get_next_line(STDIN_FILENO, &line);
	}
	close(fd[WRITE_END]);
	free(line);
}

int	handle_rw(char *file, int oflag)
{
	int	fd;

	fd = open(file, oflag, 0644);
	if (fd == -1)
		handle_exit(file);
	return (fd);
}

void	exec_read_stdin(char *delim)
{
	int		fd[2];
	int		*status;

	if (pipe(fd) == -1)
		perror("`exec_read_stdin`: Error while piping\n");
	fd[OUTPUT] = handle_rw(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC);
	parse_here_doc(delim, fd);
	status = get_signal_triggered_status();
	free(status);
	close(fd[OUTPUT]);
	dup2(fd[INPUT], STDIN_FILENO);
	close(fd[INPUT]);
}

int	sanitize_argv(t_command *cmd)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char *) * (cmd->argc + 1));
	while (cmd->argv[++i])
	{
		if (ft_strncmp(cmd->argv[i], "<<", 3) == 0)
			i += 2;
		if (cmd->argv[i])
			tmp[j++] = ft_strdup(cmd->argv[i]);
	}
	tmp[j] = NULL;
	if (j == 1 && ft_strncmp(tmp[0], "cat", 3) == 0)
	{
		tmp[j++] = ft_strdup(TMP_FILE);
		tmp[j--] = NULL;
	}
	free_matrix(cmd->argv);
	cmd->argv = tmp;
	cmd->argc = j;
	return (0);
}

int	read_input(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->argv[++i])
	{
		if (ft_strncmp(cmd->argv[i], "<<", 3) == 0 && cmd->argv[i + 1])
		{
			exec_read_stdin(cmd->argv[i + 1]);
			if (ft_strncmp(cmd->argv[0], "<<", 3) == 0)
			{
				free_matrix(cmd->argv);
				cmd->argc = 0;
				return (1);
			}
			sanitize_argv(cmd);
		}
	}
	return (0);
}
