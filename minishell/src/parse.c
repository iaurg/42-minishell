/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:30:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/02/06 15:01:49 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char **parse_input(char *input_text)
{
	char		**final_array;
	final_array = scanner(input_text);
	printf("%s",final_array[0]);
	return(final_array);
}
