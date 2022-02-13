/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/02/12 20:10:13 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return token into an array
# include "../includes/minishell.h"

int	len_token(char *str)
{
	int	len;
	len = 0;

	while (*str
	&& *str != CHAR_WHITESPACE
	&& *str != CHAR_SEMI && *str != CHAR_PIPE && *str != CHAR_LESSER
	&& *str != CHAR_GREATER && *str != CHAR_DOUBLE_QT && *str != CHAR_SINGLE_QT && *str != CHAR_EQUAL)
	{
		len++;
		str++;
	}
	if (*str == CHAR_EQUAL)
		len++;
	return (len);
}

char **scanner(char *input_text)
{
	char *a[0];
	a[0] = "xx";

	int i;
	i = 0;

	printf("%d\n", len_token(input_text));


	return (a);
}
