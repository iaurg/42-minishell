/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:08:59 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/07 18:17:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(t_list *envp[], int fd)
{
	t_list	*tmp;

	tmp = *envp;
	while (tmp)
	{
		write(fd, tmp->key, ft_strlen(tmp->key));
		write(fd, "=", 1);
		write(fd, tmp->value, ft_strlen(tmp->value));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
