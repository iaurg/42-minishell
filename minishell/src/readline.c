/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/02/04 22:18:21 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

int	take_input(char *input_text)
{
	char *buffer;

	buffer = readline("🐚~");
	if (buffer)
	{
		save_history(buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		return (0);
	}
	return (1);
}
