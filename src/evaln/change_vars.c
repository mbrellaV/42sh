///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   change_vars.c                                      :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
///*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "eval_expr.h"
//
//char			*save_to_env(char *str, int i, int dopi, char *dopstr)
//{
//	char	*str_for_rec;
//	char	*str_from_env;
//	int		res;
//
//	dprintf(2, "\nsas: |%d|\n", dopi);
//	if (str[0] == '+' || str[0] == '-')
//		str_for_rec = ft_strsub(str, 2, i);
//	else if (i > 2 && ((str[i - 2] == '+' && str[i - 1] == '+') ||
//	(str[i - 2] == '-' && str[i - 1] == '-')))
//		str_for_rec = ft_strsub(str, 0, i - 2);
//	else
//		str_for_rec = ft_strsub(str, 0, i);
//	if (!(str_from_env = ft_get_var(str_for_rec, globals()->g_all_var)))
//		res = 0;
//	else
//		res = ft_atoi(str_from_env);
//	ft_strdel(&str_from_env);
//	dopstr = ft_itoa(res + dopi);
//	set_new_var(str_for_rec, dopstr, &globals()->g_all_var);
//	ft_strdel(&str_for_rec);
//	ft_strdel(&dopstr);
//	dopstr = ft_itoa(res);
//	if (str[i] == '+' || str[i] == '-')
//	{
//		str_for_rec = ft_strjoin(dopstr, &str[i]);
//		ft_strdel(&dopstr);
//		return (str_for_rec);
//	}
//	return (dopstr);
//}
//
//char			*do_save_var(char *str)
//{
//	char	*dopstr;
//	int		i;
//	int		dopi;
//
//	i = 0;
//	dopi = 0;
//	if (check_calc_str(str) == -1)
//		return (NULL);
//	i += word_size(str);
//	if ((ft_strstr(str, "++") == str ||
//	ft_strstr(str, "--") == str) ||
//	(ft_strstr(str, "++") ||
//	ft_strstr(str, "--")))
//	{
//		dprintf(2, "\n|%d, %d, %d, %d|\n", str[0], str[1], str[i - 1], str[i - 2]);
//		if (((str[i - 1] == '-' && str[i - 2] == '-') ||
//			(str[i - 1] == '+' && str[i - 2] == '+')) &&
//			((str[0] == '-' && str[1] == '-') ||
//			(str[0] == '+' && str[1] == '+')))
//			return (NULL);
//		dprintf(2, "\n|%d, %d, %d, %d|\n", str[0], str[1], str[i - 1], str[i - 2]);
//		if ((str[i - 1] == '-' && str[i - 2] == '-') ||
//			(str[0] == '-' && str[1] == '-'))
//			dopi = -1;
//		if ((str[i - 1] == '+' && str[i - 2] == '+') ||
//			(str[0] == '+' && str[1] == '+'))
//			dopi = 1;
//		return (save_to_env(str, i, dopi, dopstr));
//	}
////	else if (!ft_strstr(str, "+") || !ft_strstr(str, "-"))
////	{
////		return (save_to_env(str, i, dopi, dopstr));
////	}
//	return (NULL);
//
//}
//
//int				zam_word_in_eval(int *i, char *evalstr, char *newstr)
//{
//	char	*dopstr;
//	char	*str_for_del;
//
//	dopstr = ft_strsub(evalstr, *i, word_size(&evalstr[*i]));
//	str_for_del = dopstr;
//	dprintf(2, "\n|%s|\n", dopstr);
//	if (!(dopstr = do_save_var(dopstr)))
//	{
//		ft_strdel(&evalstr);
//		ft_strdel(&newstr);
//		ft_strdel(&str_for_del);
//		return (-1);
//	}
//	ft_strdel(&str_for_del);
//	ft_strcat(newstr, dopstr);
//	dprintf(2, "\n|%s|\n", dopstr);
//	ft_strdel(&dopstr);
//	*i += word_size(&evalstr[*i]);
//	return (1);
//}
//
//char			*change_vars(char *evalstr)
//{
//	int		i;
//	char	*dopstr;
//	char	*newstr;
//
//	i = 0;
//	if (!(newstr = ft_memalloc(130000)))
//		return (NULL);
//	while (evalstr[i] != '\0')
//	{
//		if (ft_isalpha(evalstr[i]) == 1 || (((ft_strstr(&evalstr[i], "++") == &evalstr[i]) ||
//				(ft_strstr(&evalstr[i], "--") == &evalstr[i])) && ft_isalpha(evalstr[i + 2]) == 1))
//		{
//			if (zam_word_in_eval(&i, evalstr, newstr) == -1)
//				return (NULL);
//		}
//		else
//		{
//			dopstr = ft_strdup(" ");
//			dopstr[0] = evalstr[i];
//			ft_strcat(newstr, dopstr);
//			ft_strdel(&dopstr);
//			i++;
//		}
//	}
//	ft_strdel(&evalstr);
//	dprintf(2, "\nsas: |%s|\n", newstr);
//	return (newstr);
//}
