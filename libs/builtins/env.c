/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:08:59 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/29 20:25:28 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	env(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
