#include <unistd.h>
#include <stdio.h>

int main(int argv, char **argc)
{
	/*int i = 1;

	char buf;
	while (read(STDIN_FILENO, &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
//	return 0;
	printf("END");*/
	execve("./21sh", NULL, NULL);
	return (0);
}
