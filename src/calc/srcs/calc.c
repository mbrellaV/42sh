#include "fshell.h"

//char		*ft_do_cut(char *tmp)
//{
//	int					dopi;
//	char				*str;
//	char				*dop;
//	char				*str_for_rec;
//	char				*str_for_del;
//	t_calc_err			err_strcut_for_calc;
//
//	dopi = 0;
//	err_strcut_for_calc.status = 0;
//	err_strcut_for_calc.type = 1;
//	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
//		if (sc_size(&tmp[dopi], '(') != -1 &&
//			sc_size(&tmp[dopi + 1], '(') != -1)
//		{
//			dopi = sc_size(&tmp[dopi], '(') - 3;
//			dop = ft_strsub(tmp, 2, dopi - 2);
//			str_for_del = dop;
//			str_for_rec = ft_main_calc_rec(dop);
//			//dop = str_for_rec;
//			if (str_for_rec != NULL)
//				dop = str_for_rec;
//			dprintf(2, "\n|%s|\n", dop);
//			str = calc_ltoa(calc(dop, &err_strcut_for_calc));
//			dprintf(2, "\n|%s|\n", str);
//			(str_for_del != dop) ? ft_strdel(&str_for_del) : 0;
//			ft_strdel(&dop);
//			return (str);
//		}
//	return (NULL);
//}
//
//char		*ft_main_calc_rec(char *mas)
//{
//	char	*newstr;
//	char	*cut_str;
//	int		i;
//	int		d;
//
//	i = 0;
//	d= 0;
//	dprintf(2, "\n|%s|\n", mas);
//	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
//		return (NULL);
//	while (i < ft_strlen(mas) && mas[i] != '\0')
//	{
//		if (mas[i] == '$')
//		{
//			d++;
//			if (!(cut_str = ft_do_cut(mas + 1)))
//			{
//				ft_strdel(&newstr);
//				return (NULL);
//			}
//			i += 1 + sc_size(&mas[i + 1], mas[i + 1]);
//		}
//		else
//		{
//			cut_str = ft_strdup(" ");
//			cut_str[0] = mas[i];
//			i++;
//		}
//		ft_strcat(newstr, cut_str);
//		ft_strdel(&cut_str);
//	}
//	if (d > 0)
//		return (newstr);
//	ft_strdel(&newstr);
//	return (NULL);
//}
//
//char		*ft_do_zam_eval(char *mas)
//{
//	char				*newstr;
//
//	if (mas == NULL)
//		return (NULL);
//	if (*mas == '\0')
//		return (mas);
//	if ((newstr = ft_main_calc_rec(mas)) == NULL)
//		return (mas);
//	ft_strdel(&mas);
//	return (newstr);
//}

long long		calc(char *str, t_calc_err *error)
{
	t_calc_tkns	*calc_tokens;
	long long	res;

	if (!str || !error)
		return (0);
	if (!(calc_tokens = calc_get_arr_tkns(str, NULL, 0)))
		return (calc_error(error, CALC_ERR_LX));
	res = calc_exp(calc_tokens, 0, error);
	calc_del_tkns(calc_tokens);
	return (res);
}

long long		calc_exp(t_calc_tkns *s_tokens, size_t index, t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (s_tokens->first_token->type == CALC_END)
		return (0);
	result = calc_add_sub(s_tokens, &index, error);
	if (error->status)
		return (0);
	if (s_tokens->first_token[index].type != CALC_END)
	{
		if (s_tokens->first_token[index].type == CALC_RPARENT)
			return (calc_error(error, CALC_ERR_PARENT));
		return (calc_error(error, CALC_ERR_SYNTAX));
	}
	return (result);
}
