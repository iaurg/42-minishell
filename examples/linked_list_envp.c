#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/libft/libft.h"

t_list	*to_linked_list(char **envp)
{
	t_list	*list;
	int i;

	i = -1;
	list = NULL;
	while (envp[++i])
		ft_lstpush(&list, ft_lstnew(envp[i]));
	return (list);
}

void	display_linked_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

static int are_equal(char *one, char *other)
{
	return (ft_strncmp(one, other, ft_strlen(other)));
}

t_list	*lst_find(t_list *list, char *key)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (are_equal(tmp->content, key) == 0)
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
	if (tmp != NULL && are_equal(tmp->content, key) == 0)
	{
		*list = tmp->next;
		free(tmp);
		return (1);
	}
	while (tmp != NULL && are_equal(tmp->content, key) != 0)
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

int main(int argc, char *argv[], char *envp[])
{
	t_list	*list;
	t_list *tmp;

	list = to_linked_list(envp);
	tmp = lst_find(list, "HOME");
	lst_del_node(&list, "HOME");
	lst_del_node(&list, "PATH");
	lst_del_node(&list, "XDG_SEAT_PATH");
	lst_del_node(&list, "XDG_SESSION_PATH");
	lst_del_node(&list, "NAOTEM");
	display_linked_list(list);
}
