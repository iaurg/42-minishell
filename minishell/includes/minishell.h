/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/12 20:06:06 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"
# include "./error.h"
/* DELIMITERS */
# define CHAR_WHITESPACE ' '
# define CHAR_TAB '\t'
# define CHAR_NEWLINE '\n'

# define CHAR_PIPE '|'
# define CHAR_SEMI ';'
# define CHAR_DOLAR '$'
# define CHAR_EQUAL '='
# define CHAR_SINGLE_QT '\''
# define CHAR_DOUBLE_QT '\"'
# define CHAR_GREATER '>'
# define CHAR_DBL_GREATER '>>'
# define CHAR_LESSER '<'
# define CHAR_DBL_LESSER '<<'
# define CHAR_NULL 0

char	**parse_input(char *input_text);
int		take_input(char *input_text);
char	**scanner(char *input_text);

#endif
