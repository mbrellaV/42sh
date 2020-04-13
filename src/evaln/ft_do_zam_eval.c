/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_zam_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

char		*ft_do_cut(char *tmp, int *d)
{
	int		dopi;
	char 	*str;
	char	*dop;
	char	*str_for_rec;

    if (tmp[dopi] == '(' && tmp[dopi + 1] == '(' && !(dopi = 0))
        if (sc_size(&tmp[dopi], '(') != -1 && sc_size(&tmp[dopi + 1], '(') != -1)
        {
            dopi = sc_size(&tmp[dopi], '(') - 3;
            dop = ft_strsub(tmp, 2, dopi - 2);
            str_for_rec = ft_main_calc_rec(dop);
			if (str_for_rec == NULL)
			{
                *d += ft_strlen(tmp);
                str = ft_itoa(eval_expr(dop));
				ft_strdel(&dop);
				return (str);
            }
			else
			{
				*d += ft_strlen(tmp);
				str = ft_itoa(eval_expr(str_for_rec));
				ft_strdel(&str_for_rec);
				return (str);
			}
        }
    return (NULL);
}

char		*ft_main_calc_rec(char *mas)
{
	int		d;
	int		i;
	char	*newstr;
	char	*cut_str;

	d = 0;
	i = 0;
	if (mas == NULL)
		return (ft_strnew(130000));
	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
		return (NULL);
	while (mas[d] != '\0')
	{
		if (mas[d] == '$')
		{
			i++;
			cut_str = ft_do_cut(&mas[d + 1], &d);
			if (cut_str == NULL)
			{
				ft_strdel(&newstr);
				ft_strdel(&cut_str);
				return (NULL);
			}
			ft_strcat(newstr, cut_str);
			ft_strdel(&cut_str);
		}
		else
		{
			newstr[d] = mas[d];
			d++;
		}
	}
	if (i == 0)
	{
		ft_strdel(&newstr);
		return (NULL);
	}
	return (newstr);
}

char		*ft_do_zam_eval(char *mas)
{
	char	*newstr;

	if (*mas == '\0')
		return (mas);
    if ((newstr = ft_main_calc_rec(mas)) == NULL)
		return (mas);
    ft_strdel(&mas);
    return (newstr);
}