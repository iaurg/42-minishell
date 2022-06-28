/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/27 22:26:20 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

int	take_input(char *buffer, t_command *cmd)
{
	char	*out;
	char	*trimmed;

	(void)cmd;
	out = readline("[ minishell ]$ ");
	if (out == NULL)
	{
		free(out);
		return (1);
	}
	trimmed = ft_strtrim(out, " ");
	ft_strlcpy(buffer, trimmed, ft_strlen(trimmed) + 1);
	free(out);
	free(trimmed);
	if (ft_strlen(buffer) == 0)
		return (0);
	if (ft_strlen(buffer) > 0)
	{
		save_history(buffer);
		return (0);
	}
	return (1);
}
