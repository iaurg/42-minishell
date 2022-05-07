/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/05 22:13:23 by vwildner         ###   ########.fr       */
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

char	*ms_getenv(char *envp[], char *key)
{
	char			*envp_key;
	char			*final;
	unsigned int	i;

	i = 0;
	while (envp[i])
	{
		envp_key = ft_strtok(envp[i], "=");
		if (ft_strncmp(envp_key, key, ft_strlen(key)) == 0)
		{
			free(envp_key);
			final = ft_strchr(envp[i], '=');
			return (++final);
		}
		free(envp_key);
		i++;
	}
	return (NULL);
}

void	handle_dollar_sign(char *envp[], char **args, char *tmp, int i)
{
	size_t	len;

	len = ft_strlen(args[i]);
	if (args[i][0] == '$')
	{
		tmp = ms_getenv(envp, &args[i][1]);
		if (tmp)
		{
			free(args[i]);
			args[i] = tmp;
		}
		else if (len == 1)
			return ;
		else
		{
			free(args[i]);
			args[i] = ft_strdup("");
		}
	}
}

void	expand_args(char *args[], char *envp[])
{
	int		i;
	char	*tmp;
	size_t	len;

	i = -1;
	tmp = NULL;
	while (args[++i])
	{
		handle_dollar_sign(envp, args, tmp, i);
		if (args[i][0] == '~')
		{
			tmp = getenv("HOME");
			printf("tmp: %s\n", tmp);
			len = ft_strlen(args[i]);
			free(args[i]);
			if (len > 1)
				args[i] = ft_strjoin(tmp, &args[i][1]);
			else
				args[i] = ft_strdup(tmp);
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
