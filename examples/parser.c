#include "../libs/libft/libft.h"
#include <stdio.h>
#include <string.h>

// cc examples/parser.c -g3 libs/libft/*.c

/*
function to parse string into tokens and return array of tokens

echo "hello world" -> {echo, "hello world", NULL} (keep the quotes!)

echo "hello ' world" -> invalid input

parser split arguments with quotes.
*/

int ft_count_words(char *str, char *delim)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(delim, str[i]) == NULL)
		{
			count++;
			while (str[i] && ft_strchr(delim, str[i]) == NULL)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char **parser(char *str)
{
	char **tokens;
	char *token;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	tokens = (char **)malloc(sizeof(char *) * (ft_count_words(str, " ") + 1));
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			continue;
		}
		token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!token)
			return (NULL);
		while (str[i] && str[i] != ' ')
		{
			token[j] = str[i];
			j++;
			i++;
		}
		token[j] = '\0';
		tokens[k] = token;
		k++;
		j = 0;
	}
	tokens[k] = NULL;
	return (tokens);
}

int	main(void)
{
	printf("[0] %s \n", parser("echo 'hello world'")[0]);
	printf("[1] %s \n", parser("echo 'hello world'")[1]);
	return (0);
}
