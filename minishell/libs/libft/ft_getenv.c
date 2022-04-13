/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 07:35:14 by vwildner          #+#    #+#             */
/*   Updated: 2022/04/13 08:00:20 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_getenv(const char *env)
{
	int		i;
	int		len;
	char	*found_env;

	found_env = NULL;
	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (__environ[i] && ft_memcmp(env, __environ[i], len))
		i++;
	if (__environ[i])
		found_env = __environ[i] + len;
	return (found_env);
}
