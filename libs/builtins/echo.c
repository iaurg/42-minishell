/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:54:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/23 05:42:13 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Test command:
// gcc -Wall -Wextra -Werror -o echo_test ./libs/builtins/echo.c ./libs/libft/*.c && ./echo_test
static int	check_flag_n(char **args)
{
	if (ft_strncmp(args[1], "-n", 1) == 0)
		return (1);
	return (0);
}

int	echo(char **args, int fd)
{
	int i;
	int has_n;

	i = 1;
	has_n = check_flag_n(args);

	if (has_n)
		i++;
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if(args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if(!has_n)
		write(fd, "\n", 1);
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
