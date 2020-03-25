#include "eval_expr.h"

char	*ft_do_cut(char *tmp, int *d)
{
	int		dopi;
	char	*str;
	char    *dop;
	char    *str_for_rec;

	dopi = 0;
	str = 0;
    dprintf(2, "\n|%s|\n", tmp);
    if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
	{
        dprintf(2, "\n|%d|, |%d|\n", sc_size(&tmp[dopi], '('), sc_size(&tmp[dopi + 1], '('));
        if (sc_size(&tmp[dopi], '(') != -1 && sc_size(&tmp[dopi + 1], '(') != -1)
        {
            dopi = sc_size(&tmp[dopi], '(') - 3;
            dop = ft_strsub(tmp, 2, dopi - 2);
            dprintf(2, "\n|%s|\n", dop);
            str_for_rec = ft_main_calc_rec(dop);
			dprintf(2, "\n1|%s|\n", str_for_rec);
			if (str_for_rec == NULL)
			{
                dprintf(2, "\n2|%s|\n", str_for_rec);
                *d += ft_strlen(tmp);
                return (ft_itoa(eval_expr(dop)));
            }
			else
			{
				dprintf(2, "\n3|%s|\n", str_for_rec);
				*d += ft_strlen(tmp);
				return (ft_itoa(eval_expr(str_for_rec)));
			}
        }
	    else
        {
            return (NULL);
        }
//		dopi += 2;
//		while (tmp[dopi] != '\0')
//		{
//			dopi++;
//			if (tmp[dopi] == ')' && tmp[dopi + 1] == ')' && tmp[dopi + 2] == '\0')
//				break;
//		}
//		if (tmp[dopi] != '\0')
//		{
//			str = ft_strsub(tmp, 2, dopi - 2);
//		}
	}
    return (NULL);
}

char        *ft_main_calc_rec(char *mas)
{
	int		d;
	int i;
	char	*newstr;
	char    *cut_str;

	d = 0;
	i = 0;
	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
		return (NULL);
	while (mas[d])
	{
		if (mas[d] == '$')
		{
			i++;
			cut_str = ft_do_cut(&mas[d + 1], &d);
			dprintf(2, "\n|%s|\n", cut_str);
			if (cut_str == NULL)
				return (NULL);
			ft_strcat(newstr, cut_str);
		}
		else
		{
			newstr[d] = mas[d];
			d++;
		}
	}
	if (i == 0)
		return (NULL);
	return (newstr);
}

char        *ft_do_zam_eval(char *mas)
{
	char *newstr;

    if ((newstr = ft_main_calc_rec(mas)) == NULL)
        return (mas);
    return (newstr);
}