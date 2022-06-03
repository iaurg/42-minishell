/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:43:27 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 21:45:58 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*replace_explicit_quotes(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * (strlen(str) + 1));
	while (str[++i + 1])
	{
		if ((str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\'')))
		{
			tmp[i] = START_REPR;
			if (str[i + 1] == '\"')
				tmp[i + 1] = DQ_REPR;
			else if (str[i + 1] == '\'')
				tmp[i + 1] = SQ_REPR;
			i++;
		}
		else
			tmp[i] = str[i];
	}
	tmp[i] = str[i];
	i++;
	tmp[i] = '\0';
	return (tmp);
}

static int	odd_quote_tokens(char *str)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			j++;
		if (str[i] == '\"')
			k++;
	}
	return (j % 2 == 1 || k % 2 == 1);
}

int	handle_tokens(char *str, t_command *cmd)
{
	char	*tmp;

	tmp = replace_explicit_quotes(str);
	if (odd_quote_tokens(tmp))
	{
		cmd->status = 127;
		ft_putstr_fd("minishell: syntax error: unbalanced quotes\n",
			STDERR_FILENO);
		free(tmp);
		return (1);
	}
	cmd->argv = parser(tmp);
	return (0);
}
