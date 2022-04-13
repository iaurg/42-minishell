/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:44:48 by itaureli          #+#    #+#             */
/*   Updated: 2021/09/19 16:30:03 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*holder = NULL;
	char		*buffer;
	char		*final_line;
	int			read_fd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free_and_reset(buffer);
		return (NULL);
	}
	if (!holder)
		holder = ft_strdup("");
	read_fd = read_line(&holder, &buffer, &final_line, fd);
	free_and_reset(buffer);
	if (read_fd <= 0 && !final_line)
		return (NULL);
	return (final_line);
}

ssize_t	read_line(char **holder, char **buffer, char **final_line, int fd)
{
	ssize_t		read_result;
	char		*temp_result;

	read_result = 1;
	while (!ft_strchr(*holder, '\n') && read_result)
	{
		read_result = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[read_result] = '\0';
		temp_result = *holder;
		*holder = ft_strjoin(temp_result, *buffer);
		free(temp_result);
	}
	*final_line = split_line(holder);
	if (read_result == 0 && !(*holder)[0])
	{
		free(*holder);
		*holder = NULL;
		return (0);
	}
	if (!*final_line)
		free_and_reset(*final_line);
	return (read_result);
}

char	*split_line(char **holder)
{
	int		i;
	char	*holder_copy;
	char	*temp_holder;

	i = 0;
	while ((*holder)[i] != '\0')
	{
		if ((*holder)[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (i == 0 || !*holder)
		return (NULL);
	temp_holder = *holder;
	holder_copy = ft_substr(temp_holder, 0, i);
	*holder = ft_strdup(&(*holder)[i]);
	free_and_reset(temp_holder);
	return (holder_copy);
}

void	free_and_reset(void *var)
{
	free(var);
	var = NULL;
}
