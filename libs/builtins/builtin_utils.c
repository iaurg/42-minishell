/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:35 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/03 20:24:17 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

t_list	*ft_lstnew2(char *content)
{
	t_list	*element;
	char	**splitted;

	splitted = ft_split(content, '=');
	element = (t_list *)malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	element->key = ft_strdup(splitted[0]);
	if (splitted[1])
		element->value = ft_strdup(splitted[1]);
	else
		element->value = NULL;
	element->content = content;
	element->next = NULL;
	free_matrix(splitted);
	return (element);
}

t_list	**to_linked_list(char **envp)
{
	t_list	**list;
	int		i;

	i = -1;
	list = (t_list **)malloc(sizeof(t_list *));
	*list = NULL;
	while (envp[++i])
		ft_lstpush(list, ft_lstnew2(envp[i]));
	return (list);
}

t_command	*init_builtins(char *envp[])
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->status = 0;
	cmd->envp = to_linked_list(envp);
	return (cmd);
}

char	*ms_getenv(t_list *envp[], char *key)
{
	t_list			*tmp;

	tmp = lst_find(envp, key);
	if (tmp)
		return (tmp->value);
	return (NULL);
}

int	read_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(STDERR_FILENO, "minishell: no such file or directory: \n ", 35);
		return (0);
	}
	dup2(fd, 0);
	close(fd);
	return (fd);
}
