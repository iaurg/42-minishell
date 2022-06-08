/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:08:20 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/14 20:59:01 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/resource.h>

# define GNL_FOUND_LINEBREAK 1
# define GNL_FOUND_EOF 0
# define GNL_ERROR -1
# define MAX_FILE_DESCRIPTOR RLIMIT_NOFILE
# define GNL_BUFFER_SIZE 32

size_t	gnl_strlen(const char *s);
char	*gnl_strdup(const char *s1);
char	*gnl_strcpy(char *dest, char *src);
size_t	gnl_strlcat(char *dest, const char *src, size_t size);
char	*gnl_strchr(const char *s, int c);
int		get_next_line(int fd, char **line);

#endif
