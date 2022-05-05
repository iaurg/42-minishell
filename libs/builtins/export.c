/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:46:25 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/05 20:46:26 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	export(char *arg, char *envp[])
{
	unsigned int	i;
	char			*arg_key;
	char			*envp_key;

	arg_key = ft_strtok(arg, "=");
	i = 0;
	while (envp[i])
	{
		envp_key = ft_strtok(envp[i], "=");
		if (ft_strncmp(envp_key, arg_key, ft_strlen(arg_key)) == 0)
		{
			free(arg_key);
			free(envp_key);
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			return (0);
		}
		free(envp_key);
		i++;
	}
	free(arg_key);
	envp[i] = ft_strdup(arg);
	envp[i + 1] = NULL;
	return (0);
}
