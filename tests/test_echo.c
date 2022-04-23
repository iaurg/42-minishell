#include "../includes/builtins.h"

int	main(int argc, char **argv)
{
	int i = argc;
	//	Strange behavior when testing only with echo, with no params or flags
	echo(&argv[1], 1);
	return (i);
}
