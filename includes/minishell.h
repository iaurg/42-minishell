/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/05/12 02:15:52 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"
# include "../includes/builtins.h"
# include "./error.h"

/* DELIMITERS */
# define CHAR_WHITESPACE ' '
# define CHAR_TAB '\t'
# define CHAR_NEWLINE '\n'

# define CHAR_PIPE '|'
# define CHAR_DOLAR '$'
# define CHAR_EQUAL '='
# define CHAR_SINGLE_QT '\''
# define CHAR_DOUBLE_QT '\"'
# define CHAR_GREATER '>'
# define CHAR_DBL_GREATER '>>'
# define CHAR_LESSER '<'
# define CHAR_DBL_LESSER '<<'
# define CHAR_NULL 0

int		take_input(char *input_text, t_command *cmd);
char	**parse_input(char *input_text);
int		pwd(void);
void	signal_handler(int signal_number);

/* executors */
int		system_exec(t_command *cmd);
int		execute(t_command *cmd);

/* cleanup */
void	atexit_clean(void *data);
char	*get_abspath(t_command *cmd, char *command, const char *path);

/* redirections */
int		handle_redirections(t_command *cmd);

/* utilities */
void	print_err_msg(char *command, char *msg);
char	*solve_absolute_path(t_command *cmd);
char	**to_array(t_list **list);
#endif
