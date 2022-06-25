/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:37:49 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/25 18:40:33 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equals(const char *first)
{
	if (ft_strchr(first, '=') != NULL)
		return (1);
	return (0);
}
