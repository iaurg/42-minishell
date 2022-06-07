/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:08:33 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 22:45:15 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free(char *free_me, char const *dont_free_me)
{
	size_t	total_size;
	size_t	free_me_size;
	char	*buffer;

	free_me_size = gnl_strlen(free_me) + 1;
	total_size = free_me_size + gnl_strlen(dont_free_me);
	buffer = malloc(total_size * sizeof(char));
	if (buffer == NULL)
	{
		free(free_me);
		return (NULL);
	}
	gnl_strcpy(buffer, free_me);
	gnl_strlcat(buffer, dont_free_me, total_size);
	free(free_me);
	return (buffer);
}

static char	*initialize_line_buffer(char *read_buffer, bool *is_linebreak)
{
	char	*read_linebreak_position;
	char	*line_linebreak_position;
	char	*line_buffer;

	if (read_buffer[0] == '\0')
		return (gnl_strdup(""));
	line_buffer = gnl_strdup(read_buffer);
	read_linebreak_position = gnl_strchr(read_buffer, '\n');
	if (read_linebreak_position == NULL)
		return (line_buffer);
	*is_linebreak = true;
	line_buffer = join_and_free(line_buffer, read_buffer);
	if (line_buffer == NULL)
		return (NULL);
	line_linebreak_position = gnl_strchr(line_buffer, '\n');
	*line_linebreak_position = '\0';
	gnl_strcpy(read_buffer, read_linebreak_position + 1);
	return (line_buffer);
}

static void	set_null_line_break(char *linebreak_position,
								bool *is_linebreak,
								char *read_buffer)
{
	if (linebreak_position != NULL)
	{
		*is_linebreak = true;
		*linebreak_position = '\0';
		linebreak_position = gnl_strchr(read_buffer, '\n');
		gnl_strcpy(read_buffer, linebreak_position + 1);
	}
}

static char	*read_and_join(int fd,
							char *read_buffer,
							char *line_buffer,
							bool *is_linebreak)
{
	char		*linebreak_position;
	long int	bytes_read;

	while (*is_linebreak == false)
	{
		bytes_read = read(fd, read_buffer, GNL_BUFFER_SIZE);
		if (bytes_read < 0 || bytes_read > SSIZE_MAX)
		{
			free(line_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		line_buffer = join_and_free(line_buffer, read_buffer);
		if (line_buffer == NULL)
			return (NULL);
		linebreak_position = gnl_strchr(line_buffer, '\n');
		set_null_line_break(linebreak_position, is_linebreak, read_buffer);
		if (bytes_read == 0)
			break ;
	}
	return (line_buffer);
}

int	get_next_line(int fd, char **line)
{
	static char	read_buffer[GNL_BUFFER_SIZE + 1];
	char		*line_buffer;
	bool		is_linebreak;

	if (fd < 0 || fd > MAX_FILE_DESCRIPTOR
		|| GNL_BUFFER_SIZE <= 0 || line == NULL)
		return (GNL_ERROR);
	is_linebreak = false;
	line_buffer = initialize_line_buffer(read_buffer, &is_linebreak);
	if (line_buffer == NULL)
		return (GNL_ERROR);
	line_buffer = read_and_join(fd, read_buffer, line_buffer, &is_linebreak);
	*line = line_buffer;
	if (line_buffer == NULL)
		return (GNL_ERROR);
	if (is_linebreak)
		return (GNL_FOUND_LINEBREAK);
	return (GNL_FOUND_EOF);
}
