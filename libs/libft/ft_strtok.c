/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:44:07 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/01 22:44:09 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char *delim)
{
	char	*token;

	token = str;
	if (ft_strchr(str, *delim) != NULL)
		token = ft_substr(str, 0, ft_strchr(str, *delim) - str);
	return (token);
}
