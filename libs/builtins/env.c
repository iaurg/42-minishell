/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:08:59 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/20 05:09:00 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	env(void)
{
	int	i;

	i = -1;
	while (__environ[++i])
	{
		write(STDOUT_FILENO, __environ[i], ft_strlen(__environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
