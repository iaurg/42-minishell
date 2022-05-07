/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:19 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/06 22:17:58 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

static t_command	*get_command(void)
{
	static t_command	*cmd;

	if (!cmd)
		cmd = (t_command *)malloc(sizeof(t_command));
	return (cmd);
}

static t_builtin	translate_builtin(char *name)
{
	if (ft_strncmp(name, "cd", 2) == 0)
		return (CD);
	if (ft_strncmp(name, "env", 3) == 0)
		return (ENV);
	if (ft_strncmp(name, "echo", 4) == 0)
		return (ECHO);
	if (ft_strncmp(name, "export", 6) == 0)
		return (BUILTINS_EXPORT);
	if (ft_strncmp(name, "unset", 5) == 0)
		return (UNSET);
	if (ft_strncmp(name, "exit", 4) == 0)
		return (EXIT);
	return (SIZE);
}

static t_command	*init_builtins(char *args[], char *envp[])
{
	t_command	*cmd;
	int			argc;
	t_builtin	builtin;

	argc = 0;
	builtin = translate_builtin(args[0]);
	cmd = get_command();
	while (args[argc])
		argc++;
	cmd->argc = argc;
	cmd->argv = args;
	cmd->envp = envp;
	cmd->builtin = builtin;
	return (cmd);
}

static int	try_builtins_exec(char *args[], char *envp[])
{
	t_command	*cmd;
	int			status;

	status = 1;
	cmd = init_builtins(args, envp);
	status = run(cmd);
	free(cmd);
	return (status);
}

int	execute(char *args[], char *envp[])
{
	pid_t		pid;
	int			status;

	if(!args[0])
		return (1);
	if (try_builtins_exec(args, envp) == 0)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error forking");
		return (0);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
