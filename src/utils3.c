/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:37:49 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/19 16:38:58 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equals(const char *first)
{
	if (ft_strchr(first, '=') != NULL)
		return (1);
	return (0);
}
