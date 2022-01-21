/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/20 22:28:13 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int take_input(char *input_text)
{
	char *buffer;

	buffer = readline("🐚~");
	if (buffer)
	{
		add_history(buffer);
		printf("%s\n", buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		// ft_str(input_text, buffer);
		return (0);
	}
	else
	{
		return (1);
	}
}

int	main(void)
{
	char buffer[1024];
	while (1)
	{
		take_input(buffer);
	}

	return (0);
}
