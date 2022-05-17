/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/15 06:44:52 by vwildner         ###   ########.fr       */
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
