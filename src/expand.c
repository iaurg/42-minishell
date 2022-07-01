/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/08 23:32:04 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status(t_command *cmd, int i)
{
	if (cmd->argv[i][1] == '?'
		&& cmd->argv[i][2] == '\0')
	{
		free(cmd->argv[i]);
		cmd->argv[i] = ft_itoa(cmd->status);
		return (1);
	}
	return (0);
}

int	handle_quotes(t_command *cmd, char *arg, int i)
{
	char	*token;

	token = ft_strchr(cmd->argv[i], *arg);
	if (token != NULL)
	{
		while (token != NULL)
		{
			ft_memmove(token, token + 1, ft_strlen(token));
			token = ft_strchr(cmd->argv[i], *arg);
		}
		return (1);
	}
	return (0);
}

int	count_n_dollar(const char *str)
{
	int i;
	int n_dollar;

	i = -1;
	n_dollar = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			n_dollar++;
	}
	printf("n dollar %d\n", n_dollar);
	return (n_dollar);
}

char **split_dollar_tokens(t_command *cmd, const char *str)
{
	int n_dollar = count_n_dollar(str);
	int i;
	char *tmp;
	int j;
	char **tokens;

	i = 0;
	j = 0;
	tokens = (char **)malloc(sizeof(char *) * (n_dollar + 1));
	while (str[++i])
	{
		tmp = ms_getenv(cmd->envp, &str[i]);
		if (tmp)
			tokens[j++] = ft_strdup(tmp);
		free(tmp);
		while (str[i] && str[i] != '$' && n_dollar > 1)
				i++;
	}
	tokens[j] = NULL;
	for (int i=0; tokens[i]; i++)
		printf("tok[%i] = %s\n", tokens[i]);
	return (tokens);
}


void	handle_dollar_sign(t_command *cmd, char *tmp, int i)
{
	size_t	len;
	char	*token;

	len = ft_strlen(cmd->argv[i]);
	token = ft_strchr(cmd->argv[i], '$');
	if (token != NULL)
	{
		printf("%s\n", token);
		if (handle_status(cmd, i))
			return ;
		char **tmp = split_dollar_tokens(cmd, token);
		tmp = ms_getenv(cmd->envp, ++token);
		if (tmp)
		{
			printf("tmp: %s\n", tmp);
			free(cmd->argv[i]);
			cmd->argv[i] = ft_strdup(tmp);
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

void	handle_home(t_command *cmd, char *tmp, int i)
{
	char	*sign_start;
	char	*tmp_arg;

	if (ft_strchr(cmd->argv[i], '~') != NULL)
	{
		tmp_arg = ft_strdup(cmd->argv[i]);
		sign_start = ft_strchr(tmp_arg, '~');
		tmp = ms_getenv(cmd->envp, "HOME");
		free(cmd->argv[i]);
		if (++sign_start != NULL)
			cmd->argv[i] = ft_strjoin(tmp, sign_start);
		else
			cmd->argv[i] = ft_strdup(tmp);
		free(tmp_arg);
	}
}

void	expand_args(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd->argv[++i])
	{
		if (cmd->s_quotes >= 2 && handle_quotes(cmd, "\'", i))
			continue ;
		if (cmd->d_quotes >= 2)
			handle_quotes(cmd, "\"", i);
		if (!(ft_strncmp(cmd->argv[i], "$", 2) == 0))
			handle_dollar_sign(cmd, tmp, i);
		handle_home(cmd, tmp, i);
	}
	cmd->argc = i;
}
