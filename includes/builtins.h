/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:01:22 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/14 01:03:53 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H
# define MAX_ARGS 256

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "../libs/libft/libft.h"
# include <fcntl.h>

typedef enum builtin {
	ECHO,
	CD,
	ENV,
	BUILTINS_EXPORT,
	EXIT,
	UNSET,
	SIZE
}	t_builtin;

typedef struct s_command {
	int			argc;
	int			fd;
	char		**argv;
	t_list		**envp;
	t_builtin	builtin;
	int			status;
}	t_command;

typedef int	t_dispatcher(t_command *cmd);

/* internal functions */
int			env(t_list *envp[], int fd);
int			export(char *arg, t_list *envp[]);
int			echo(char **args, int fd);
int			cd(char **args, t_list *envp[]);
int			cd_home(t_list *envp[]);
int			set_oldpwd(t_list *envp[], char *buf);
int			unset(char *argv[], t_list *envp[], size_t size);

/* public interface */
int			builtins_echo(t_command *cmd);
int			builtins_pwd(t_command *cmd);
int			builtins_export(t_command *cmd);
int			builtins_env(t_command *cmd);
int			builtins_exit(t_command *cmd);
int			builtins_unset(t_command *cmd);
int			builtins_cd(t_command *cmd);

/* executors */
int			run(t_command *cmd);

/* utils */
t_command	*init_builtins(char *envp[]);
t_list		*lst_find(t_list **list, char *key);
int			lst_del_node(t_list **list, char *key);
char		*ms_getenv(t_list *envp[], char *key);
t_list		*ft_lstnew2(char *content);
int			read_file(char *filename);
void		print_err_msg(char *command, char *msg);

#endif
