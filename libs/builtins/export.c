/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:46:25 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/07 22:54:00 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	export(char *arg, t_list *envp[])
{
	t_list			*exists;
	char			*arg_key;

	arg_key = ft_strtok(arg, "=");
	exists = lst_find(envp, arg_key);
	if (exists)
		lst_del_node(envp, arg_key);
	ft_lstpush(envp, ft_lstnew2(arg));
	free(arg_key);
	return (0);
}
