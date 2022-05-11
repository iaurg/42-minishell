/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/11 18:33:32 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listlen(t_list **list)
{
	t_list	*tmp;
	int	len;

	len = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**to_array(t_list **list)
{
	char	**array;
	t_list	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_listlen(list);
	tmp = *list;
	array = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		array[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (array);
}

char	*solve_absolute_path(t_command *cmd)
{
	char	*first_arg;
	char	*all_paths;

	first_arg = cmd->argv[0];
	if (*first_arg == '/' || *first_arg == '.')
		return (first_arg);
	all_paths = ms_getenv(cmd->envp, "PATH");
	return (get_abspath(cmd, first_arg, all_paths));
}

int	system_exec(t_command *cmd)
{
	pid_t		pid;
	int			status;
	char		*abspath;
	char		**compat_envp;

	pid = fork();
	if (pid == 0)
	{
		compat_envp = to_array(cmd->envp);
		abspath = solve_absolute_path(cmd);
		if (execve(abspath, cmd->argv, compat_envp) == -1)
			perror("Command not found");
		free(compat_envp);
		free(abspath);
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
