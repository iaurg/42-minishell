/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:50:02 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/07 18:19:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": ", 2);
}
