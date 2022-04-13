/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/13 08:38:11 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

/*
Your shell should:

[x] • Display a prompt when waiting for a new command.

[x] • Have a working history.

[ ] • Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

[ ] • Not use more than one global variable. Think about it. You will have to explain its purpose.

[x] • Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).

[ ] • Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.

[ ] • Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).

[ ] • Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

[ ] • Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

[ ] • Handle environment variables ($ followed by a sequence of characters) which should expand to their values.

[ ] • Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

[ ] • Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

[ ] • In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.

[ ] • Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks

*/

static void	shell_prefix_handler(int signal)
{
	char cwd[1025];

	if (signal == SIGINT)
	{
		getcwd(cwd, 1024);
		ft_putstr_fd("\033[2D\033[0K", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd("\r\033[1;31muser@minishell\033[0;0m", STDERR_FILENO);
		ft_putstr_fd(":\033[1;34m", STDERR_FILENO);
		ft_putstr_fd(cwd, STDERR_FILENO);
		ft_putstr_fd("\033[0;0m$ ", STDERR_FILENO);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char buffer[1024];

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	pwd();
	while (1)
	{
		signal(SIGINT, shell_prefix_handler);
		if (take_input(buffer))
			break;
		parse_input(buffer);
	}
	return (0);
}
