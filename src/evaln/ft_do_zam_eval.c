#include "../../inc/fshell.h"

char	*ft_do_cut(char *tmp, int *d)
{
	int		dopi;
	char	*str;

	dopi = 0;
	str = 0;
	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
	{
		dopi += 2;
		while (tmp[dopi] != '\0')
		{
			dopi++;
			if (tmp[dopi] == ')' && tmp[dopi + 1] == ')' && tmp[dopi + 2] == '\0')
				break;
		}
		if (tmp[dopi] != '\0')
		{
			str = ft_strsub(tmp, 2, dopi - 2);
		}
	}
	*d += ft_strlen(tmp);
	return (ft_itoa(eval_expr(str)));
}

int		ft_do_zam_eval(char **mas)
{
	int		i;
	int		d;
	char	*newstr;

	i = 0;
	while (mas[i])
	{
		d = 0;
		if (!(newstr = ft_memalloc(ft_strlen(mas[i]) + 1)))
			return (-1);
		while (mas[i][d])
		{
			if (mas[i][d] == '$')
				ft_strcat(newstr, ft_do_cut(&mas[i][d + 1], &d));
			else
			{
				newstr[d] = mas[i][d];
				d++;
			}
		}
		ft_strdel(&mas[i]);
		mas[i] = newstr;
		i++;
	}
	return (0);
}