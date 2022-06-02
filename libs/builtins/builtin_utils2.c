/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:34:34 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 22:41:51 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	first_char_is_equal(const char *first)
{
	if (ft_strncmp(first, "=", 1) == 0)
		return (1);
	return (0);
}

void	print_err_msg(char *command, char *msg)
{
	char	*err_msg;

	err_msg = ft_strdup("minishell: ");
	err_msg = ft_strjoin(err_msg, command);
	err_msg = ft_strjoin(err_msg, ": ");
	err_msg = ft_strjoin(err_msg, msg);
	err_msg = ft_strjoin(err_msg, "\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

static int	are_equal(char *one, char *other)
{
	return (ft_strncmp(one, other, ft_strlen(other)));
}

t_list	*lst_find(t_list **list, char *key)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (are_equal(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	lst_del_node(t_list **list, char *key)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *list;
	prev = NULL;
	if (tmp != NULL && are_equal(tmp->key, key) == 0)
	{
		*list = tmp->next;
		free(tmp);
		return (1);
	}
	while (tmp != NULL && are_equal(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	prev->next = tmp->next;
	free(tmp);
	return (1);
}
