#include "../../includes/builtins.h"

/*
[getcwd](https://man7.org/linux/man-pages/man3/getcwd.3.html): These functions return a null-terminated string containing an absolute pathname that is the current working directory of the calling process. The pathname is returned as the function result and via the argument buf, if present.

[chdir](https://man7.org/linux/man-pages/man2/chdir.2.html): changes the current working directory of the calling process to the directory specified in path
*/

int	cd(void)
{
	printf("cd mini");
	return (0);
}
