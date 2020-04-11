/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_zam_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

char		*do_cut_help(char *str, char *dop, char *str_for_rec)
{
	if (str_for_rec == NULL)
	{
		str = ft_itoa(eval_expr(dop));
		ft_strdel(&dop);
	}
	else
	{
		str = ft_itoa(eval_expr(str_for_rec));
		ft_strdel(&str_for_rec);
	}
	return (str);
}

char		*ft_do_cut(char *tmp, int *d)
{
	int		dopi;
	char	*str;
	char	*dop;
	char	*str_for_rec;

	dopi = 0;
	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
		if (sc_size(&tmp[dopi], '(') != -1 &&
			sc_size(&tmp[dopi + 1], '(') != -1)
		{
			dopi = sc_size(&tmp[dopi], '(') - 3;
			dop = ft_strsub(tmp, 2, dopi - 2);
			str_for_rec = ft_main_calc_rec(dop);
			*d += ft_strlen(tmp);
			return (do_cut_help(str, dop, str_for_rec));
		}
	return (NULL);
}

char		*ft_calc_h(char *mas, char *newstr, int d)
{
	char	*cut_str;

	cut_str = ft_do_cut(&mas[d + 1], &d);
	if (cut_str == NULL)
	{
		ft_strdel(&newstr);
		ft_strdel(&cut_str);
		return (NULL);
	}
	ft_strcat(newstr, cut_str);
	ft_strdel(&cut_str);
	return (newstr);
}

char		*ft_main_calc_rec(char *mas)
{
	int		i;
	int		d;
	char	*newstr;

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
			if (!(newstr = ft_calc_h(mas, newstr, d)))
				return (NULL);
		}
		else
		{
			newstr[d] = mas[d];
			d++;
		}
	}
	return (calc_check(newstr, i));
}

char		*ft_do_zam_eval(char *mas)
{
	char	*newstr;

	if ((newstr = ft_main_calc_rec(mas)) == NULL)
		return (mas);
	return (newstr);
}
