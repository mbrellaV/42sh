#include "main.h"

int					ft_strlen(const char *src)
{
	register int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char				*ft_strdup(char *src)
{
	int				i;
	char			*ret;

	if (!(ret = malloc(ft_strlen(src) + 1)))
		return (NULL);
	i = -1;
	while (src[++i])
		ret[i] = src[i];
	ret[i] = '\0';
	return (ret);
}

int					ft_strcmp(const char *s11, const char *s22)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char*)s11;
	s2 = (unsigned char*)s22;
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] == '\0' && s2[i] != '\0') || (s1[i] != '\0' && s2[i] == '\0'))
		return (s1[i] - s2[i]);
	return (0);
}
