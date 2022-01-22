/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/01/22 16:31:31 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	take_input(char *input_text)
{
	char *buffer;

	buffer = readline("🐚~");
	if (buffer)
	{
		add_history(buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		return (0);
	}
	return (1);
}
