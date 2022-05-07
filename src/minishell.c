/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/07 05:53:00 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handle_dollar_sign(t_command *cmd, char *tmp, int i)
{
	size_t	len;

	len = ft_strlen(cmd->argv[i]);
	if (cmd->argv[i][0] == '$')
	{
		tmp = ms_getenv(cmd->envp, &cmd->argv[i][1]);
		if (tmp)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = tmp;
		}
		else if (len == 1)
			return ;
		else
		{
			free(cmd->argv[i]);
			cmd->argv[i] = ft_strdup("");
		}
	}
}

void	expand_args(t_command *cmd)
{
	int		i;
	char	*tmp;
	size_t	len;

	i = -1;
	tmp = NULL;
	while (cmd->argv[++i])
	{
		handle_dollar_sign(cmd, tmp, i);
		if (cmd->argv[i][0] == '~')
		{
			tmp = getenv("HOME");
			len = ft_strlen(cmd->argv[i]);
			free(cmd->argv[i]);
			if (len > 1)
				cmd->argv[i] = ft_strjoin(tmp, &cmd->argv[i][1]);
			else
				cmd->argv[i] = ft_strdup(tmp);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char		buffer[1024];
	int			status;
	t_command	*cmd;

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	cmd = init_builtins(envp);
	status = 1;
	while (status)
	{
		if (take_input(buffer))
			break ;
		cmd->argv = parse_input(buffer);
		expand_args(cmd);
		status = execute(cmd);
	}
	free(cmd);
	return (0);
}
