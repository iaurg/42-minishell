/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:43:27 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/02 19:26:13 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	replace_if_matches(char *origin, char match, char replacement)
{
	if (*origin == match)
		*origin = replacement;
}

static void	tokenize_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], '\'', dbl_qt_repr);
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i], '\"', qt_repr);
		}

	}
}

static void	recover_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], dbl_qt_repr, '\'');
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i],qt_repr, '\"');
		}

	}
}

static int	odd_nbr_quote_tokens(char *str)
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
	tokenize_internal_quotes(str, SQ_REPR, DQ_REPR);
	if (odd_nbr_quote_tokens(str))
	{
		cmd->status = 127;
		ft_putstr_fd("minishell: syntax error: unbalanced quotes\n",
			STDERR_FILENO);
		return (1);
	}
	recover_internal_quotes(str, SQ_REPR, DQ_REPR);
	cmd->argv = parse_whitespace(str, "\'\"");
	return (0);
}
