/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:01:22 by vwildner          #+#    #+#             */
/*   Updated: 2022/04/19 23:49:17 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H
# define MAX_ARGS 256

# include <unistd.h>
# include <stdio.h>
#include <stdlib.h>
# include "../libs/libft/libft.h"

typedef enum builtin {
	ECHO,
	CD,
	ENV,
	EXPORT,
	SIZE
}	t_builtin;

typedef struct s_command {
	int			argc;
	char		*argv[MAX_ARGS];
	char		*envp[MAX_ARGS];
	t_builtin	builtin;
}	t_command;

typedef int	t_dispatcher(t_command *cmd);

/* internal functions */
int			env(void);

/* public interface */
int			builtins_echo(t_command *cmd);
int			builtins_pwd(t_command *cmd);
int			builtins_export(t_command *cmd);
int			builtins_env(t_command *cmd);

/* executors */

int	run(t_command *cmd);

#endif
