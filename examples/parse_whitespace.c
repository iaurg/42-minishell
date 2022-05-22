#include "../includes/minishell.h"
// cc -g3 $(find src/ -type f \( -iname "*.c" ! -iname "minishell*" \)) libs/libft/*.c examples/parse_whitespace.c libs/builtins/*.c libs/get_next_line/*.c -lreadline -o parse_whitespace

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
