#include "../includes/builtins.h"

int	main(int argc, char **argv)
{
	char *args[] = {
		"-n",
		"test",
		"test2",
		"test3",
		"-n",
		NULL
	};

	echo(&argv[1], 1);
	return (0);
}
