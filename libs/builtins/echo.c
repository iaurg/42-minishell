/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:54:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/21 13:34:58 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Test command:
// gcc -Wall -Wextra -Werror -o echo_test ./libs/builtins/echo.c ./libs/libft/*.c && ./echo_test
int	echo(char **args, int fd)
{
	int i = 0;

	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		write(fd, " ", 1);
		i++;
	}
	return (0);
}
