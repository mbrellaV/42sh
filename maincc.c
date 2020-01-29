#include "stdlib.h"
#include <unistd.h>

int		main()
{
	while (malloc(1000000))
	{
		;
	}
	while (malloc(10))
	{
		;
	}
	while (malloc(1))
	{
		;
	}
	execve("./21sh", NULL, NULL);
	while (1)
	{
		;
	}
}
