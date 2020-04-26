/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_zam_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

int			check_symbols(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '*' && str[i] != '/'
		&& str[i] != '+' && str[i] != '-' && isword(str[i]) <= 0 &&
			str[i] != '%' && str[i] != '(' && str[i] != ')'
			&& str[i] != ' ' && str[i] != '\t' && is_system_symbol(str[i]) != 1)
		{
			ft_strdel(&str);
			put_error_to_shell(2);
			ft_dprintf(globals()->all_opened_fds[2], "parse error in eval near: |%c|\n", str[i]);
			return (-1);
		}
		i++;
	}
	return (1);
}
//
//char		*ft_do_cut(char *tmp)
//{
//	int		dopi;
//	char	*str;
//	char	*dop;
//	char	*str_for_rec;
//	char	*str_for_del;
//
//	dopi = 0;
//	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
//		if (sc_size(&tmp[dopi], '(') != -1 &&
//			sc_size(&tmp[dopi + 1], '(') != -1)
//		{
//			dopi = sc_size(&tmp[dopi], '(') - 3;
//			dop = ft_strsub(tmp, 2, dopi - 2);
//			str_for_del = dop;
//			str_for_rec = ft_main_calc_rec(dop);
//			if (str_for_rec != NULL)
//				dop = str_for_rec;
//			if (check_symbols(dop, str_for_del) == -1)
//				return (NULL);
//			str = ft_itoa(eval_expr(dop));
//			(str_for_del != dop) ? ft_strdel(&str_for_del) : 0;
//			ft_strdel(&dop);
//			return (str);
//		}
//	return (NULL);
//}

//char		*ft_main_calc_rec(char *mas)
//{
//	char	*newstr;
//	char	*cut_str;
//	int		i;
//
//	i = 0;
//	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
//		return (NULL);
//	while (*mas != '\0' && *mas != '$')
//	{
//		newstr[i++] = *mas;
//		mas++;
//	}
//	if (*mas == '$')
//	{
//		if (!(cut_str = ft_do_cut(mas + 1)))
//		{
//			ft_strdel(&newstr);
//			return (NULL);
//		}
//		ft_strcat(newstr, cut_str);
//		ft_strdel(&cut_str);
//		return (newstr);
//	}
//	ft_strdel(&newstr);
//	return (NULL);
//}

char		*ft_do_cut(char *tmp, int *error)
{
	int					dopi;
	char				*str;
	char				*dop;
	char				*str_for_rec;
	char				*str_for_del;

	dopi = 0;
	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
		if (sc_size(&tmp[dopi], '(') != -1 &&
			sc_size(&tmp[dopi + 1], '(') != -1)
		{
			dopi = sc_size(&tmp[dopi], '(') - 3;
			dop = ft_strsub(tmp, 2, dopi - 2);
			str_for_del = dop;
			str_for_rec = ft_main_calc_rec(dop, error);
			if (*error == 1)
				return (NULL);
			if (str_for_rec != NULL)
				dop = str_for_rec;
			str = ft_itoa(eval_expr(dop, error));
			(str_for_del != dop) ? ft_strdel(&str_for_del) : 0;
			//ft_strdel(&dop);
			if (*error == 1)
			{
				ft_strdel(&str);
				return (NULL);
			}
			return (str);
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
	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
		return (NULL);
	while (i < ft_strlen(mas) && mas[i] != '\0')
	{
		if (mas[i] == '$')
		{
			d++;
			if (!(cut_str = ft_do_cut(mas + 1, error)))
			{
				ft_strdel(&newstr);
				return (NULL);
			}
			i += sc_size(&mas[i + 1], mas[i + 1]);
		}
		else
		{
			cut_str = ft_strdup(" ");
			cut_str[0] = mas[i];
			i++;
		}
		ft_strcat(newstr, cut_str);
		ft_strdel(&cut_str);
	}
	if (d > 0)
		return (newstr);
	ft_strdel(&newstr);
	return (NULL);
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
		if (error == 1)
		{
			ft_dprintf(globals()->all_opened_fds[2], "parse error in eval near: |%s|\n", mas);
			ft_strdel(&mas);
			return (NULL);
		}
		return (mas);
	}
	ft_strdel(&mas);
	return (newstr);
}
