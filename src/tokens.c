/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:43:27 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/22 01:26:15 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	replace_explicit_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[(++i) + 1])
	{
		if ((str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\'')))
		{
			str[i] = START_REPR;
			if (str[i + 1] == '\"')
				str[i + 1] = DQ_REPR;
			else if (str[i + 1] == '\'')
				str[i + 1] = SQ_REPR;
		}
	}
	return (0);
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

	replace_explicit_quotes(str);
	if (odd_quote_tokens(str))
	{
		cmd->status = 127;
		ft_putstr_fd("minishell: syntax error: unbalanced quotes\n",
			STDERR_FILENO);
		return (1);
	}
	cmd->argv = parse_whitespace(str, "\"\'");
	return (0);
}
