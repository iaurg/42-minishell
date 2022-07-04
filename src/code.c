/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/07/04 20:17:27 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_mini_parse(char *src, char **dest, int *i, int *n_tokens)
{
	char	c;
	int		size;
	char	*end;

	c = src[*i];
	if (src[*i + 1] && (src[*i] == '\'' || src[*i] == '\"')
		&& (ft_strchr(&src[*i + 1], '\'') || ft_strchr(&src[*i + 1], '\"')))
	{
		end = ft_strchr(&src[*i + 1], c);
		size = end - &src[*i] + 2;
		dest[*n_tokens] = (char *)ft_calloc(size, sizeof(char));
		ft_strlcpy(dest[(*n_tokens)++], &src[*i], size);
		*i += size - 2;
	}
	else
	{
		dest[*n_tokens] = ft_strtok(&src[*i], " ");
		*i += ft_strlen(dest[(*n_tokens)++]) - 1;
	}
}

void	mini_parse(char *src, char **dest)
{
	int		i;
	int		n_tokens;

	i = -1;
	n_tokens = 0;
	while (src[++i])
	{
		while (src[i] == ' ' || src[i] == '\t' || src[i] == '\a'
			|| src[i] == '\r' || src[i] == '\v' || src[i] == '\f')
			i++;
		_mini_parse(src, dest, &i, &n_tokens);
	}
	dest[n_tokens] = NULL;
}
