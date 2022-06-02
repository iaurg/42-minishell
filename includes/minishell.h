/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/06/01 21:00:57 by itaureli         ###   ########.fr       */
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

/* TOKENIZER */
# define START_REPR '#'
# define DQ_REPR '\r'
# define SQ_REPR '\f'

/* TEMPORARY REFERENCES */
# define TMP_FILE "/tmp/here_doc_tmp_file"

/* file i/o */
# define INPUT 0
# define OUTPUT 1

/* pipe ends */
# define READ_END 0
# define WRITE_END 1

/* parsers */
int		take_input(char *input_text, t_command *cmd);
int		read_input(char *buffer, t_command *cmd);
char	**parse_input(char *input_text);
void	expand_args(t_command *cmd);
char	**parse_whitespace(char *str, char *delims);
char	**join_args(char **args, char delim);
int		ft_count_words(char *str, char *delim);

/* executors */
int		system_exec(t_command *cmd);
int		execute(t_command *cmd);
int		handle_execute(t_command *cmd);
void	execute_pipe(int *flag, int *fds, t_command *cmd, int pos);

/* cleanup */
void	atexit_clean(void *data);
char	*get_abspath(t_command *cmd, char *command, const char *path);

/* redirections */
int		handle_redirections(t_command *cmd);

/* signals */
void	signal_handler(int signal_number);
void	child_signal_handler(int signal_number);

/* utilities */
void	print_err_msg(char *command, char *msg);
void	decoupled_shell_display(void);
char	*get_last_slash_arg(char *arg);
void	handle_exit(const char *s);
int		handle_tokens(char *str, t_command *cmd);
char	*solve_absolute_path(t_command *cmd);
char	**to_array(t_list **list);

/* signal handlers */
int		*get_signal_triggered_status(void);
void	handle_heredoc_signal(int signal_number);

#endif
