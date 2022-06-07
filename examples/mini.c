#include "../libs/libft/libft.h"
#include <stdio.h>

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

int	mini_parse(char *src, char **dest)
{
	int		i;
	int		n_tokens;
	int		size;
	char	*end;
	char	c;

	i = -1;
	n_tokens = 0;
	while (src[++i])
	{
		while (src[i] == ' ' || src[i] == '\t' || src[i] == '\a'
			|| src[i] == '\r'|| src[i] == '\v' || src[i] == '\f')
			i++;
		c = src[i];
		if (src[i + 1] && (src[i] == '\'' || src[i] == '\"')
			&& (ft_strchr(&src[i + 1], '\'') || ft_strchr(&src[i + 1], '\"')))
		{
			end = ft_strchr(&src[i + 1], c);
			size = end - &src[i] + 2;
			dest[n_tokens] = (char *)ft_calloc(size, sizeof(char));
			ft_strlcpy(dest[n_tokens++], &src[i], size);
			i += size - 2;
		}
		else
		{
			dest[n_tokens] = ft_strtok(&src[i], " ");
			i += ft_strlen(dest[n_tokens++]) - 1;
		}
	}
	dest[n_tokens] = NULL;
}


int main(void)
{
	char *str = "echo \'hello world\' out";
	char **dest;
	int n_tokens = ft_count_words(str, " ");
	printf("tokens: %d\n", n_tokens);
	dest = (char **)ft_calloc(n_tokens, sizeof(char *));
	mini_parse(str, dest);
	for (int i = 0; dest[i]; i++)
		printf("dest[%i]: `%s`\n", i, dest[i]);
	free_matrix(dest);
}
