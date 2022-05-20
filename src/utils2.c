/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 02:27:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/05/20 04:50:47 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_listlen(t_list **list)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**to_array(t_list **list)
{
	char	**array;
	t_list	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_listlen(list);
	tmp = *list;
	array = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		array[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (array);
}

void	handle_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

char *replace_explicit_quotes(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * (strlen(str) + 1));
	while (str[++i + 1])
	{
		if ((str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\'')))
		{
			tmp[i] = '#';
			if (str[i + 1] == '\"')
				tmp[i + 1] = '^';
			else if (str[i + 1] == '\'')
				tmp[i + 1] = '$';
			i++;
		}
		else
			tmp[i] = str[i];
	}
	tmp[i] = str[i];
	i++;
	tmp[i] = '\0';
	return (tmp);
}

char *clear_quotes(char *str)
{
	int i;
	int j;
	char *tmp;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i + 1])
	{
		if ((str[i] == '#' && (str[i + 1] == '^' || str[i + 1] == '$')))
		{
			if (str[i + 1] == '^')
				tmp[j] = '\"';
			else if (str[i + 1] == '$')
				tmp[j] = '\'';
			if (str[i + 2])
				i++;
		}
		else
			tmp[j] = str[i];
		j++;
	}
	tmp[j] = str[i];
	i++;
	j++;
	tmp[j] = '\0';
	return (tmp);
}

char **map_clear_quotes(char **args)
{
	int i;
	char	**final;

	i = 0;
	while (args[i])
		i++;
	final = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (args[++i])
		final[i] = clear_quotes(args[i]);
	free_matrix(args);
	return (final);
}

int	odd_quote_tokens(char *str, t_command *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	**args;

	i = -1;
	j = 0;
	k = 0;
	tmp = replace_explicit_quotes(str);
	while (tmp[++i])
	{
		if (tmp[i] == '\'')
			j++;
		if (tmp[i] == '\"')
			k++;
	}
	if (j % 2 == 1 || k % 2 == 1)
	{
		cmd->status = 127;
		ft_putstr_fd("minishell: syntax error: unbalanced quotes\n",
			STDERR_FILENO);
		return (1);
	}
	args = parse_whitespace(tmp, "\'\"");
	cmd->argv = map_clear_quotes(args);
	return (0);
}
