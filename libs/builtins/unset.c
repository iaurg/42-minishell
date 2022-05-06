/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:27:35 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/05 23:54:48 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	ft_swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	unset(char *envp[], char *argv[])
{
	char			*envp_key;
	char			*key;;
	unsigned int	i;
	unsigned int	pos;

	i = 0;
	pos = 0;
	if (argv[1] != NULL)
		key = argv[1];
	else
		return (1);
	while (envp[i])
	{
		envp_key = ft_strtok(envp[i], "=");
		if (ft_strncmp(envp_key, key, ft_strlen(key)) == 0)
			pos = i;
		free(envp_key);
		i++;
	}
	if (!pos)
		return (1);
	while (envp[i])
		i++;
	free(envp[pos]);
	envp[pos] = NULL;
	ft_swap(&envp[pos], &envp[i - 1]);
	return (0);
}
