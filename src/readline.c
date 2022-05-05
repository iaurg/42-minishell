/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/04 22:57:28 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

static char	*get_last_slash_arg(char *arg)
{
	char	*args[256];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
		{
			args[j] = &arg[i + 1];
			j++;
		}
		i++;
	}
	return (args[j - 1]);
}

static char	*get_inline_shell_display(void)
{
	char	cwd[1025];
	char	*tmp;
	char	*other;
	char	*path;

	getcwd(cwd, 1024);
	path = get_last_slash_arg(cwd);
	tmp = ft_strdup("\r\033[1;31m[user@minishell ");
	other = ft_strjoin(tmp, path);
	free(tmp);
	tmp = ft_strjoin(other, "]$ \033[0;0m");
	free(other);
	return (tmp);
}

int	take_input(char *input_text)
{
	char	*buffer;
	char	*display;

	display = get_inline_shell_display();
	buffer = readline(display);
	free(display);
	if (buffer)
	{
		save_history(buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		return (0);
	}
	return (1);
}
