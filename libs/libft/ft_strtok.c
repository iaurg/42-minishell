#include "libft.h"

char	*ft_strtok(char *str, char *delim)
{
	char	*token;

	token = str;
	if (ft_strchr(str, *delim) != NULL)
		token = ft_substr(str, 0, ft_strchr(str, *delim) - str);

	return (token);
}
