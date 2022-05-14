/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:48:05 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/14 00:42:09 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*decoupled_shell_display(void)
{
	char	cwd[1025];
	char	*tmp;
	char	*other;
	char	*path;
	char	*tmp_user;

	getcwd(cwd, 1024);
	path = get_last_slash_arg(cwd);
	tmp_user = ft_strdup(getenv("USER"));
	tmp = ft_strjoin(tmp_user, "\033[0;31m@minishell ");
	other = ft_strjoin(tmp, path);
	free(tmp_user);
	free(tmp);
	tmp = ft_strjoin(other, " ~ $\033[0m ");
	ft_putstr_fd(tmp, 1);
	free(other);
	return (tmp);
}
