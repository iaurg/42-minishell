/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 21:01:00 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listlen(t_list **list)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**to_array(t_list **list)
{
	char	**array;
	t_list	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_listlen(list);
	tmp = *list;
	array = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		array[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (array);
}

void	handle_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

char	*clear_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i + 1])
	{
		if ((str[i] == START_REPR
				&& (str[i + 1] == DQ_REPR || str[i + 1] == SQ_REPR)))
		{
			if (str[i + 1] == DQ_REPR)
				tmp[j++] = '\"';
			else if (str[i + 1] == SQ_REPR)
				tmp[j++] = '\'';
			i++;
		}
		else
			tmp[j++] = str[i];
	}
	tmp[j++] = str[i];
	tmp[j] = '\0';
	return (tmp);
}

int ft_count_words(char *str, char *delim)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(delim, str[i]) == NULL)
		{
			count++;
			while (str[i] && ft_strchr(delim, str[i]) == NULL)
				i++;
		}
		else
			i++;
	}
	return (count);
}
