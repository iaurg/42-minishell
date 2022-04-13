/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:26:51 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/13 19:38:46 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_token(char *str)
{
	int	len;

	len = 0;
	while (*str
		&& *str != CHAR_WHITESPACE
		&& *str != CHAR_PIPE && *str != CHAR_LESSER
		&& *str != CHAR_GREATER && *str != CHAR_DOUBLE_QT
		&& *str != CHAR_SINGLE_QT && *str != CHAR_EQUAL)
	{
		len++;
		str++;
	}
	if (*str == CHAR_EQUAL)
		len++;
	return (len);
}

int	count_tokens(char *str)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (str[i])
	{
		len = len_token(&str[i]);
		if (len > 0)
		{
			count++;
			i += len;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (len == 0 || src == 0)
		return (dst);
	*dst = *src;
	if (*src != 0)
		ft_strncpy(dst + 1, ++src, --len);
	else if (*src == 0)
		ft_strncpy(dst + 1, src, --len);
	return (dst);
}

char	**parse_input(char *input_text)
{
	char	**final_array;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	final_array = (char **)malloc(sizeof(char *) * (count_tokens(input_text) + 1));
	while (input_text[i])
	{
		len = len_token(&input_text[i]);
		if (len > 0)
		{
			final_array[j] = (char *)malloc(sizeof(char) * (len + 1));
			ft_strncpy(final_array[j], &input_text[i], len);
			final_array[j][len] = '\0';
			i += len;
			j++;
		}
		else
		{
			if (input_text[i] == CHAR_DOUBLE_QT)
			{
				len = 0;
				while (input_text[++i] != CHAR_DOUBLE_QT){
					len++;
				}
				final_array[j] = (char *)malloc(sizeof(char) * (len + 1));
				ft_strncpy(final_array[j], &input_text[i - len], len);
				final_array[j][len] = '\0';
				i += len;
				j++;
			}
			else
				i++;
		}
	}
	final_array[j] = NULL;
	return (final_array);
}
