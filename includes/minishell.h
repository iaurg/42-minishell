/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/06/27 22:27:17 by itaureli         ###   ########.fr       */
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

# include "builtins.h"
# include "error.h"

/* TOKENIZER */
# define DQ_REPR 25
# define SQ_REPR 26

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
void	expand_args(t_command *cmd);
char	**parser(char *str);
void	mini_parse(char *src, char **dest);

/* executors */
int		system_exec(t_command *cmd);
int		execute(t_command *cmd);
int		handle_execute(t_command *cmd);
void	execute_pipe(int *flag, int *fds, t_command *cmd, int pos);

/* cleanup */
char	*get_abspath(t_command *cmd, char *command, const char *path);

/* redirections */
int		handle_redirections(t_command *cmd);
int		set_fd(t_command *cmd);

/* signals */
void	signal_handler(int signal_number);
void	child_signal_handler(int signal_number);
void	newline_hook(int sig);

/* utilities */
void	print_err_msg(char *command, char *msg);
void	handle_exit(const char *s);
int		handle_tokens(char *str, t_command *cmd);
char	*solve_absolute_path(t_command *cmd);
char	**to_array(t_list **list);
void	recover_internal_quotes(char *str, char qt_repr, char dbl_qt_repr);
int		ft_count_words(char *str, char *delim);
void	free_tmp(char *tmp, char *line);
int		using_prohibited_characters(char *buff, t_command *cmd);

/* signal handlers */
int		*get_signal_triggered_status(void);
void	handle_heredoc_signal(int signal_number);

/* entrypoint */
int		minishell(char *envp[]);

#endif
