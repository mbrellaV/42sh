#include <unistd.h>

int main(void)
{
	if (!fork())
	{
		execl("21sh", NULL);
	}
}
