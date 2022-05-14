/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:35 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/14 10:20:41 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include <string.h>
t_list	*ft_lstnew2(char *content)
{
	t_list	*element;
	char	**splitted;

	splitted = ft_split(content, '=');
	element = (t_list *)malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	element->key = splitted[0];
	element->value = splitted[1];
	element->content = content;
	element->next = NULL;
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

static int are_equal(char *one, char *other)
{
	return (ft_strncmp(one, other, ft_strlen(other)));
}

t_list	*lst_find(t_list **list, char *key)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (are_equal(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	lst_del_node(t_list **list, char *key)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *list;
	prev = NULL;
	if (tmp != NULL && are_equal(tmp->key, key) == 0)
	{
		*list = tmp->next;
		free(tmp);
		return (1);
	}
	while (tmp != NULL && are_equal(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	prev->next = tmp->next;
	free(tmp);
	return (1);
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
		fprintf(stderr, "bash: no such file or directory: %s\n", filename);
		return (0);
	}
	dup2(fd, 0);
	close(fd);
	return (fd);
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
