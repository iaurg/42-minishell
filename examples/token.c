#include "../includes/minishell.h"
#include "../libs/libft/libft.h"
#include <stdio.h>
// cc -g3 $(find src/ -type f \( -iname "*.c" ! -iname "minishell*" \)) libs/libft/*.c examples/token.c libs/builtins/*.c libs/get_next_line/*.c -lreadline

int main(void)
{
	char str[] = "\\\'\\\"\0";
	char *tmp;

	printf("str: `%s`\n", str);
	replace_explicit_quotes(str); // #\r#\t
	printf("post: `%s`\n", str);
}
