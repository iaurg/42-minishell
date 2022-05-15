/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:48:05 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/15 03:56:44 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	decoupled_shell_display(void)
{
	char	cwd[1025];
	char	hostname[257];
	char	*tmp;
	char	*path;
	char	*tmp_user;

	getcwd(cwd, 1024);
	gethostname(hostname, 256);
	path = get_last_slash_arg(cwd);
	tmp = ft_strdup("\033[1;31m");
	tmp_user = ft_strdup(getenv("USER"));
	tmp = ft_strjoin(tmp, tmp_user);
	tmp = ft_strjoin(tmp, "\033[0;36m@");
	tmp = ft_strjoin(tmp, hostname);
	tmp = ft_strjoin(tmp, " \033[0;34m");
	tmp = ft_strjoin(tmp, path);
	tmp = ft_strjoin(tmp, " ~ $\033[0m ");
	free(tmp_user);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	free(tmp);
}
