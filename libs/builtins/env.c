/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:08:59 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/07 03:27:39 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	env(t_list *envp[])
{
	t_list	*tmp;

	tmp = *envp;
	while (tmp)
	{
		write(STDOUT_FILENO, tmp->key, ft_strlen(tmp->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value));
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
