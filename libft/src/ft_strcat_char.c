#include "../inc/libft.h"

void		ft_strcat_char(char *buf, char c)
{
	char	*dopstr;

	dopstr = ft_strdup(" ");
	dopstr[0] = c;
	ft_strcat((char *)buf, dopstr);
	ft_strdel(&dopstr);
}