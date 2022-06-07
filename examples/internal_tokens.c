#include "../libs/libft/libft.h"
#include <stdio.h>


static void	replace_if_matches(char *origin, char match, char replacement)
{
	if (*origin == match)
		*origin = replacement;
}

static void	tokenize_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], '\'', dbl_qt_repr);
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i], '\"', qt_repr);
		}

	}
}

static void	recover_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], dbl_qt_repr, '\'');
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i],qt_repr, '\"');
		}

	}
}


int	main(void)
{
	char str[] = "testing \"this internal \' string\" and now we are outside";
	char str2[] = "testing \'this internal \" string\' and now we are outside";
	char *p;

	p = str;
	tokenize_internal_quotes(p, 25, 26);
	printf("to: %s\n", p);
	recover_internal_quotes(p, 25, 26);
	printf("de: %s\n", p);

	p = str2;
	tokenize_internal_quotes(p, 25, 26);
	printf("to: %s\n", p);
	recover_internal_quotes(p, 25, 26);
	printf("de: %s\n", p);

	char str3[] = "testing with \'starting quote \"but with no ending";
	p = str3;
	tokenize_internal_quotes(p, 25, 26);
	printf("to: %s\n", p);
}
