#include "../libs/libft/libft.h"
#include <stdio.h>
#include <string.h>

// cc examples/parser.c -g3 libs/libft/*.c

/*
function to parse string into tokens and return array of tokens

echo "hello world" -> {echo, "hello world", NULL} (keep the quotes!)

echo "hello ' world" -> invalid input

parser split arguments with quotes.

Read again:
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
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
			i++;
		if (str[i] == '"')
		{
			token = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!token)
				return (NULL);
			j = 0;
			token[j++] = str[i++];
			while (str[i] && str[i] != '"')
				token[j++] = str[i++];
			token[j++] = str[i++];
			token[j] = '\0';
			tokens[k] = token;
			k++;
			i++;
			continue;
		}
		while (str[i] && str[i] != ' ')
			token[j++] = str[i++];
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
	char *str = strdup("echo \"hello ''' '''' """" world\"");
	int i;
	i = 0;
	while (parser(str)[i])
	{
		printf("`%s` \n", parser(str)[i]);
		i++;
	}

	i = 0;
	str = strdup("echo \"hello world with a big string inside this crazy thing\"");
	while (parser(str)[i])
	{
		printf("`%s` \n", parser(str)[i]);
		i++;
	}
	/*
	i = 0;
	str = strdup("echo test > ls >> ls >> ls ; echo test >> ls; cat ls");
	while (parser(str)[i])
	{
		printf("`%s` \n", parser(str)[i]);
		i++;
	}
	/*
	i = 0;
	while (parser("cat | cat | cat")[i])
	{
		printf("`%s` \n", parser("cat | cat | cat")[i]);
		i++;
	}

	i = 0;
	while (parser("echo | | echo $? exit")[i])
	{
		printf("`%s` \n", parser("echo | | echo $? exit")[i]);
		i++;
	}

	i = 0;
	while (parser("echo oi && echo tchau | wc -l echo 1 exit")[i])
	{
		printf("`%s` \n", parser("echo oi && echo tchau | wc -l echo 1 exit")[i]);
		i++;
	}
	*/
	return (0);
}
