#include <stdlib.h>
#include <stdio.h>

int main()
{
	int len = 10;
	float d;
	int i;

	d = len / 1.247;
	printf ("d = %f\n", d);
	d *= 2;
	printf ("d = %f\n", d);
	i = (int)d;
	if ((i % 2) != 0)
		i = i / 2 + 1;
	else
		i /= 2;
	printf ("i = %d\n", i);
	exit (3);
}
