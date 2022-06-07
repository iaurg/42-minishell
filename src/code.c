/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/06 23:39:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//char	**parser(char *str)
//{
//	char	**tokens;
//	char	*token;
//	int		i;
//	int		j;
//	int		k;

//	i = 0;
//	j = 0;
//	k = 0;
//	tokens = (char **)malloc(sizeof(char *) * (ft_count_words(str, " ") + 1));
//	if (!tokens)
//		return (NULL);
//	while (str[i])
//	{
//		if (str[i] == ' ')
//			i++;
//		if (str[i] == '"' || str[i] == '\'')
//		{
//			token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
//			if (!token)
//				return (NULL);
//			j = 0;
//			token[j++] = str[i++];
//			while (str[i] && str[i] != '"')
//				token[j++] = str[i++];
//			token[j++] = str[i++];
//			token[j] = '\0';
//			tokens[k] = token;
//			k++;
//			i++;
//			continue ;
//		}
//		token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
//		if (!token)
//			return (NULL);
//		while (str[i] && str[i] != ' ')
//			token[j++] = str[i++];
//		token[j] = '\0';
//		tokens[k] = token;
//		k++;
//		j = 0;
//	}
//	tokens[k] = NULL;
//	return (tokens);
//}

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
