#include "../../inc/fshell.h"

int				operator_size(char *str)
{
	int i;

	i = 0;
	while (*str != 0 && isoperator(*str) > 0)
	{
		str++;
		i++;
	}
	return (i);
}

int				word_size(char *str)
{
	int i;

	i = 0;
	if (isoperator(*str) > 0)
		return (operator_size(str));
	if (isword(*str) == 2)
		return (c_size(str, *str));
	if (isword(*str) == 3)
		return (sc_size(str, *str));
	while (*str)
	{
		if (isword(*str) == 3)
			return (i + sc_size(str, *str));
		if (isword(*str) == 0)
			return (i);
		i++;
		str++;
	}
	return (i);
}

int				sc_size(char *str, char b)
{
	int		i;
	int		cn;
	char	dop;

	i = 0;
	dop = b;
	cn = 1;
	b = find_pair_sc(b);
	if (*str == b)
		return (-2);
	while (*str != '\0' && cn != 0)
	{
		i++;
		str++;
		if (*str == dop)
			cn++;
		if (*str == b)
			cn--;
	}
	if (*str == '\0' && cn != 0)
		return (-1);
	return (i + 1);
}

int					c_size(char *str, char b)
{
	int i;

	i = 0;
	str++;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		i++;
		str++;
	}
	return (i);
}
