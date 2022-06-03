/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/01 22:24:47 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parser(char *str)
{
	char	**tokens;
	char	*token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tokens = (char **)malloc(sizeof(char *) * (ft_count_words(str, " ") + 1));
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!token)
				return (NULL);
			j = 0;
			token[j++] = str[i++];
			while (str[i] && str[i] != '"')
				token[j++] = str[i++];
			token[j++] = str[i++];
			token[j] = '\0';
			tokens[k] = token;
			k++;
			i++;
			continue ;
		}
		token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!token)
			return (NULL);
		while (str[i] && str[i] != ' ')
			token[j++] = str[i++];
		token[j] = '\0';
		tokens[k] = token;
		k++;
		j = 0;
	}
	tokens[k] = NULL;
	return (tokens);
}
