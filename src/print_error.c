/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:50:02 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/13 19:33:47 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": ", 2);
}
