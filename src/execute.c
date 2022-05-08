/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:19 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/08 02:15:50 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include <fcntl.h>

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

int	execute(t_command *cmd)
{
	if (!cmd->argv[0])
		return (1);
	if (try_builtins_exec(cmd) == 0)
		return (1);
	return (system_exec(cmd));
}
