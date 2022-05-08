/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/08 02:28:03 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**to_array(t_list **list)
{
	char	**array;
	t_list	*tmp;
	int		i;
	int		size;

	size = 0;
	i = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	array = (char **)malloc(sizeof(char *) * (size + 1));
	tmp = *list;
	while (tmp)
	{
		array[i] = tmp->content;
		tmp = tmp->next;
		i++;
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
	return (get_abspath(first_arg, all_paths));
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
	}
	return (1);
}
