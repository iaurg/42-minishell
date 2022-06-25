/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/25 18:38:58 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_inner_tokens(char *src, char **dest, int *i, int *n_tokens)
{
	int	size;
	int	start;

	size = ft_strchr(&src[*i], ' ') - &src[*i];
	if (size < 0 || size > 300)
		size = ft_strlen(&src[*i]);
	start = *i;
	while (size--)
	{
		if (src[*i] == '>' || src[*i] == '<' || src[*i] == '|')
		{
			if (*i != start)
				dest[(*n_tokens)++] = ft_strtok(&src[start], &src[*i]);
			dest[*n_tokens] = malloc(sizeof(char) * (2));
			ft_strlcpy(dest[(*n_tokens)++], &src[(*i)++], 2);
			dest[*n_tokens] = ft_strtok(&src[*i], " ");
			*i += ft_strlen(dest[(*n_tokens)++]) - 1;
			return ;
		}
		*i += 1;
	}
	*i = start;
	dest[*n_tokens] = ft_strtok(&src[*i], " ");
	*i += ft_strlen(dest[(*n_tokens)++]) - 1;
}

static void	_mini_parse(char *src, char **dest, int *i, int *n_tokens)
{
	int		size;
	char	*end;

	if (src[*i + 1] && (src[*i] == '\'' || src[*i] == '\"')
		&& (ft_strchr(&src[*i + 1], '\'') || ft_strchr(&src[*i + 1], '\"')))
	{
		end = ft_strchr(&src[*i + 1], src[*i]);
		size = end - &src[*i] + 2;
		dest[*n_tokens] = (char *)ft_calloc(size, sizeof(char));
		ft_strlcpy(dest[(*n_tokens)++], &src[*i], size);
		*i += size - 2;
	}
	else
	{
		parse_inner_tokens(src, dest, i, n_tokens);
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
