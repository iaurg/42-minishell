/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:37:49 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/25 18:40:33 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equals(const char *first)
{
	if (ft_strchr(first, '=') != NULL)
		return (1);
	return (0);
}

int	export_strjoin(t_command *cmd, char *tmp, int status)
{
	tmp = ft_strjoin(cmd->argv[1], "=");
	status = export(tmp, cmd->envp);
	free(tmp);
	return (status);
}
