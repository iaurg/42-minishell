/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:43:27 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/06 23:26:32 by vwildner         ###   ########.fr       */
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

void	recover_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
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
				replace_if_matches(&str[i], qt_repr, '\"');
		}
	}
}

static int	odd_nbr_quote_tokens(t_command *cmd, char *str)
{
	int		i;
	int		single_quotes;
	int		double_quotes;

	i = -1;
	single_quotes = 0;
	double_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == '\"')
			double_quotes++;
	}
	cmd->s_quotes = single_quotes;
	cmd->d_quotes = double_quotes;
	return (single_quotes % 2 == 1 || double_quotes % 2 == 1);
}

int	handle_tokens(char *str, t_command *cmd)
{
	int	i;
	int	n_tokens;

	tokenize_internal_quotes(str, SQ_REPR, DQ_REPR);
	if (odd_nbr_quote_tokens(cmd, str))
	{
		cmd->status = 127;
		ft_putstr_fd("minishell: syntax error: unbalanced quotes\n",
			STDERR_FILENO);
		return (1);
	}
	n_tokens = ft_count_words(str, " ");
	cmd->argv = (char **)ft_calloc(n_tokens + 1, sizeof(char *));
	mini_parse(str, cmd->argv);
	i = -1;
	while (cmd->argv[++i])
		recover_internal_quotes(cmd->argv[i], SQ_REPR, DQ_REPR);
	return (0);
}
