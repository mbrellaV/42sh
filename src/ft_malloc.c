#include "../inc/fshell.h"

void		*ft_malloc(size_t size)
{
	char	*ret;
	size_t	i;

	ret = malloc(size);
	if (!ret)
		exit(228);
	i = 0;
	while (i < size)
		ret[i++] = 0;
	return ((void*)ret);
}