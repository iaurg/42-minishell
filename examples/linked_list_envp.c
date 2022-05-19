#include "../includes/builtins.h"
#include "../libs/libft/libft.h"

// compile with:
// cc examples/linked_list_envp.c -g -C libs/libft/*.c libs/builtins/*.c -o example_linked_list_envp

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

int main(int argc, char *argv[], char *envp[])
{
	t_list	**list;
	t_list *tmp;

	char *my_env[] = {
		"PATH=/usr/bin:/bin:/usr/sbin:/sbin",
		"HOME=/home/vwildner",
		NULL
	};
	list = to_linked_list(envp);
	ft_lstclear(list, free);
}
