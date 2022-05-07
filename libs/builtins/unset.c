/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:35 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/07 04:45:55 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	unset(char *argv[], t_list *envp[], size_t size)
{
	t_list			*exists;
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		exists = lst_find(envp, argv[i]);
		if (exists)
			lst_del_node(envp, argv[i]);
		i++;
	}
	return (0);
}
