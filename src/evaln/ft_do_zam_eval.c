/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_zam_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char		*return_with_del(char *str)
{
	ft_strdel(&str);
	return (NULL);
}

char		*ft_do_cut(char *tmp, int *error)
{
	int					di;
	char				*str;
	char				*dop;
	char				*str_for_rec;
	char				*str_for_del;

	di = 0;
	if (tmp[di] == '(' && tmp[di + 1] == '(' && sc_size(&tmp[di], '(') != -1 &&
	sc_size(&tmp[di + 1], '(') != -1)
	{
		di = sc_size(&tmp[di], '(') - 3;
		dop = ft_strsub(tmp, 2, di - 2);
		str_for_del = dop;
		str_for_rec = ft_main_calc_rec(dop, error);
		if (*error == 1)
			return (return_with_del(str_for_del));
		if (str_for_rec != NULL)
			dop = str_for_rec;
		str = ft_itoa(eval_expr(dop, error, NULL));
		(str_for_del != dop) ? ft_strdel(&str_for_del) : 0;
		ft_strdel(&dop);
		return ((*error == 1) ? return_with_del(str) : str);
	}
	return (NULL);
}

char		*ft_main_calc_rec(char *mas, int *error)
{
	char	*newstr;
	char	*cut_str;
	int		i;
	int		d;

	i = 0;
	d = 0;
	newstr = ft_malloc(ft_strlen(mas) + 1);
	while (i < (int)ft_strlen(mas) && mas[i] != '\0')
	{
		if (mas[i] == '$' && ++d)
		{
			if (!(cut_str = ft_do_cut(mas + i + 1, error)))
				return (return_with_del(newstr));
			i += sc_size(&mas[i + 1], mas[i + 1]);
		}
		else
		{
			cut_str = ft_strdup(" ");
			cut_str[0] = mas[i++];
		}
		ft_strcat(newstr, cut_str);
		ft_strdel(&cut_str);
	}
	return ((d > 0) ? newstr : return_with_del(newstr));
}

char		*ft_do_zam_eval(char *mas)
{
	char				*newstr;
	int					error;

	error = 0;
	if (mas == NULL)
		return (NULL);
	if (*mas == '\0')
		return (mas);
	if ((newstr = ft_main_calc_rec(mas, &error)) == NULL)
	{
		if (error != 0)
		{
			put_error_to_shell(2);
			ft_strdel(&mas);
			return (NULL);
		}
		return (mas);
	}
	ft_strdel(&mas);
	return (newstr);
}
