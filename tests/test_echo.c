#include "../includes/builtins.h"

int	main(int argc, char **argv)
{
	int i = argc;

	echo(&argv[1], 1);
	return (i);
}
