/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_whitespace_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:01:30 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/21 03:41:11 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_end(char **args, char delim)
{
	int	i;

	i = 1;
	while (args[i] && args[i + 1])
	{
		if (ft_strchr(args[i], delim))
			break ;
		i++;
	}
	return (++i);
}

static char	**malloc_mat(char **args)
{
	char	**to_malloc;
	int		i;

	i = 0;
	while (args[i])
		i++;
	to_malloc = malloc(sizeof(char *) * (i + 1));
	if (!to_malloc)
		return (NULL);
	return (to_malloc);
}

char	*join_str(char *tmp, char **args, int *i)
{
	char	*other;

	other = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strjoin(other, args[(*i) + 1]);
	free(other);
	(*i)++;
	return (tmp);
}

char	**_join_args(char **args, char delim, char **final, char *tmp)
{
	int	i;
	int	j;
	int	end_index;

	i = -1;
	j = 0;
	while (args[++i])
	{
		tmp = ft_strdup(args[i]);
		if (args[i][0] == delim && args[i][ft_strlen(args[i]) - 1] != delim)
		{
			end_index = find_end(&args[i], delim);
			while (--end_index)
				tmp = join_str(tmp, args, &i);
		}
		final[j++] = ft_strdup(tmp);
		free(tmp);
	}
	final[j] = NULL;
	free_matrix(args);
	return (final);
}

char	**join_args(char **args, char delim)
{
	char	**final;
	char	*tmp;

	tmp = NULL;
	final = malloc_mat(args);
	return (_join_args(args, delim, final, tmp));
}
