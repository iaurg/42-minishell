#include "../libs/libft/libft.h"
#include <stdio.h>

// cc examples/parse_whitespace.c -g3 libs/libft/*.c

int find_end(char **args, char delim)
{
	int	i;

	i = 1;
	while (args[i] && args[i + 1])
	{
		if (ft_strchr(args[i], delim))
			break ;
		i++;
	}
	return (++i);
}

char **malloc_mat(char **args)
{
	char	**to_malloc;
	int		i;

	i = 0;
	while (args[i])
		i++;
	to_malloc = malloc(sizeof(char *) * (i + 1));
	if (!to_malloc)
		return (NULL);
	return (to_malloc);
}

char **join_args(char **args, char delim)
{
	int		end_index;
	int		i;
	int		j;
	char	*tmp;
	char	*other;
	char	**final;

	final = malloc_mat(args);
	i = -1;
	j = 0;
	while (args[++i])
	{
		tmp = ft_strdup(args[i]);
		if (args[i][0] == delim && args[i][ft_strlen(args[i]) - 1] != delim)
		{
			end_index = find_end(&args[i], delim);
			while (--end_index)
			{
				other = ft_strjoin(tmp, " ");
				free(tmp);
				tmp = ft_strjoin(other, args[i + 1]);
				free(other);
				i++;
			}
		}
		final[j++] = ft_strdup(tmp);
		free(tmp);
	}
	final[j] = NULL;
	free_matrix(args);
	return (final);
}

char **merge_by(char **args, char *delimiters)
{
	int	i;
	char	**final;

	i = 0;
	final = join_args(args, delimiters[i]);
	while (delimiters[++i])
		final = join_args(final, delimiters[i]);
	return (final);
}

char **parse_whitespace(char *str, char *delims)
{
	char	**args;
	char	**final;

	args = ft_split(str, ' ');
	final = merge_by(args, delims);
	return (final);
}

int main(void)
{
	char	str[] = "echo \"hello new world\" \"$PATH\" this is a \'test case\'";
	char	delims[] = "\"\'";
	char	**final = parse_whitespace(str, delims);

	printf("final args are: \n");
	for (int i = 0; final[i]; i++)
		printf("final[%i] = `%s`\n", i, final[i]);
	free_matrix(final);
}
