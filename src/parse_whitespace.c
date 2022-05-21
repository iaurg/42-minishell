/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:01:30 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/21 03:18:24 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**merge_by(char **args, char *delimiters)
{
	int		i;
	char	**final;

	i = 0;
	final = join_args(args, delimiters[i]);
	while (delimiters[++i])
		final = join_args(final, delimiters[i]);
	return (final);
}

char	**parse_whitespace(char *str, char *delims)
{
	char	**args;
	char	**final;

	args = ft_split(str, ' ');
	final = merge_by(args, delims);
	return (final);
}
