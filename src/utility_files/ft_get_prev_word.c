#include "fshell.h"

int			is_first_word(char *str, int i)
{
	while (i > 0 && isword(str[i]) == 1)
	{
		i--;
	}
	if (i == 0)
		return (1);
	else
		return (0);
}

char		*ft_get_prev_word(char *str, int i)
{
	char	*newstr;
	int		d;

	d = 0;
	if (!str)
		return (NULL);
	if (!(newstr = ft_strnew(ft_strlen(str) + 10)))
		ft_error_q(2);
	i--;
	while (i > 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	while (i > 0 && isword(str[i]) == 1)
		i--;
	if (i != 0)
		i++;
	while (isword(str[i]) == 1)
	{
		newstr[d] = str[i];
		i++;
		d++;
	}
	newstr[d] = '\0';
	return (newstr);
}