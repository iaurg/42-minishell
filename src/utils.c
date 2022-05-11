/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:55 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/11 18:26:46 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		atexit_clean(void *data);

static void	clean(void)
{
	atexit_clean(NULL);
}

void	atexit_clean(void *data)
{
	static void	*static_ptr;

	if (data)
	{
		static_ptr = data;
		atexit(clean);
	}
	else
		free(static_ptr);
}

char	*help_slash_merge(char const *origin, char const *other)
{
	char	*merged;
	char	*tmp;

	if (!origin || !other)
		return (NULL);
	tmp = malloc(ft_strlen(origin) + ft_strlen(other) + 2);
	if (!tmp)
		return (NULL);
	merged = tmp;
	while (*origin)
		*tmp++ = *origin++;
	*tmp++ = '/';
	while (*other)
		*tmp++ = *other++;
	*tmp = '\0';
	return (merged);
}

void	print_err_msg(char *command, char *msg)
{
	char	*err_msg;

	err_msg = ft_strdup("bash: ");
	err_msg = ft_strjoin(err_msg, command);
	err_msg = ft_strjoin(err_msg, ": ");
	err_msg = ft_strjoin(err_msg, msg);
	err_msg = ft_strjoin(err_msg, "\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

char	*get_abspath(t_command *cmd, char *command, const char *path)
{
	char	*file;
	char	*dir;
	int		diff;

	while (*path)
	{
		diff = ft_strchr(path, ':') - path;
		if (diff < 0)
			diff = ft_strlen(path);
		dir = ft_substr(path, 0, diff);
		file = help_slash_merge(dir, command);
		free(dir);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		if (ft_strlen(path) < (size_t)diff)
			break ;
		path += diff;
		if (*path)
			path++;
	}
	print_err_msg(command, "command not found");
	cmd->status = 127;
	exit(EXIT_FAILURE);
	return (NULL);
}
