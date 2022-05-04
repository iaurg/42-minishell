/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/03 22:48:51 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute(char *args[], char *envp[])
{
	pid_t		pid;
	pid_t		wpid;
	int			status;

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
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

//void	handle_inner_arg(char *args)
//{
//	if (args[i] == '(')
//	{
//		clean_arg = strtok(args[i], ")");
//		tmp = shell_precedence(clean_arg, envp);
//		if (tmp)
//		{
//			free(args[i]);
//			*args[i] = tmp;
//		}
//	}
//}

void	handle_dollar_sign(char **args, char *tmp, int i)
{
	if (args[i][0] == '$')
	{
		tmp = getenv(&args[i][1]);
		if (tmp)
		{
			free(args[i]);
			args[i] = tmp;
		}
	}
}

void	expand_args(char *args[], char *envp[])
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (args[++i])
	{
		handle_dollar_sign(args, tmp, i);
		if (args[i][0] == '~')
		{
			tmp = getenv("HOME");
			if (tmp)
			{
				free(args[i]);
				args[i] = ft_strjoin(tmp, &args[i][1]);
			}
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	buffer[1024];
	char	**args;
	int		status;

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	status = 1;
	while (status)
	{
		if (take_input(buffer))
			break ;
		args = parse_input(buffer);
		expand_args(args, envp);
		status = execute(args, envp);
	}
	return (0);
}
