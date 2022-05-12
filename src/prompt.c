/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:48:05 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/12 06:04:06 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*decopled_shell_display()
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
