/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:54:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/21 13:17:43 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Test command:
// gcc -Wall -Wextra -Werror -o echo_test ./libs/builtins/echo.c ./libs/libft/*.c && ./echo_test
int	echo(char **args, int fd)
{
	int i = 1;

	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		write(fd, " ", 1);
		i++;
	}
	return (0);
}

int	main(void)
{
	char *args[] = {
		"echo",
		"-n",
		"test",
		"test2",
		"test3",
		"-n",
		NULL
	};

	echo(args, 1);
	return (0);
}
