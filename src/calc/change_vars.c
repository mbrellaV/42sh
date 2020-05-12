/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 23:22:54 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

char			*save_to_env(char *str, int i, int dopi, char *dopstr)
{
	char	*str_for_rec;
	char	*str_from_env;
	int		res;

	if (dopi == 0)
		return (ft_strdup("0"));
	if (str[0] == '+' || str[0] == '-')
		str_for_rec = ft_strsub(str, 2, i);
	else if (i > 2 && ((str[i - 2] == '+' && str[i - 1] == '+') ||
	(str[i - 2] == '-' && str[i - 1] == '-')))
		str_for_rec = ft_strsub(str, 0, i - 2);
	else
		str_for_rec = ft_strsub(str, 0, i);
	if (!(str_from_env = ft_get_var(str_for_rec, globals()->g_all_var)))
		res = 0;
	else
		res = ft_atoi(str_from_env);
	ft_strdel(&str_from_env);
	dopstr = ft_itoa(res + dopi);
	set_new_var(str_for_rec, dopstr, &globals()->g_all_var);
	ft_strdel(&str_for_rec);
	ft_strdel(&dopstr);
	dopstr = ft_itoa(res);
	return (dopstr);
}

char			*do_save_var(char *str)
{
	char	*dopstr;
	int		i;
	int		opr_inc_side[2];

	i = 0;
	opr_inc_side[0] = 0;
	opr_inc_side[1] = 0;
	dopstr = NULL;
	i += word_size(str);
	if (i > 1 && (str[i - 1] == '-' && str[i - 2] == '-'))
		opr_inc_side[1] = -1;
	if (i > 1 && (str[i - 1] == '+' && str[i - 2] == '+'))
		opr_inc_side[1] = 1;
	if ((str[0] == '-' && str[1] == '-'))
		opr_inc_side[0] = -1;
	if ((str[0] == '+' && str[1] == '+'))
		opr_inc_side[0] = 1;
	if (opr_inc_side[0] != 0 && opr_inc_side[1] != 0)
		return (NULL);
	if (i > 0 && is_incr_sym(str[i - 1]) && (opr_inc_side[0] == 0 &&
	opr_inc_side[1] == 0) && (dopstr = ft_strjoin("0", &str[i - 1])))
		return (dopstr);
	return (save_to_env(str, i, opr_inc_side[0] + opr_inc_side[1], dopstr));
}

int				zam_word_in_eval(int *i, char *evalstr, char *newstr)
{
	char	*dopstr;
	char	*str_for_del;

	dopstr = ft_strsub(evalstr, *i, calc_word_size(&evalstr[*i]));
	*i += calc_word_size(&evalstr[*i]);
	str_for_del = dopstr;
	if (!(dopstr = do_save_var(dopstr)))
	{
		ft_strdel(&evalstr);
		ft_strdel(&newstr);
		ft_strdel(&str_for_del);
		return (-1);
	}
	ft_strdel(&str_for_del);
	ft_strcat(newstr, dopstr);
	ft_strdel(&dopstr);
	return (1);
}

static void		change_vars_help(char **dopstr, char **evalstr, int *i,
									char *newstr)
{
	*dopstr = ft_strsub(evalstr[*i], 0, calc_word_size(evalstr[*i + 1]) + 1);
	ft_strcat(newstr, *dopstr);
	ft_strdel(dopstr);
	*i += word_size(evalstr[*i]);
}

char			*change_vars(char *evalstr)
{
	int		i;
	char	*dopstr;
	char	*newstr;

	i = 0;
	if (!(newstr = ft_memalloc(130000)))
		return (NULL);
	while (evalstr[i] != '\0')
	{
		if (evalstr[i] == '$')
			change_vars_help(&dopstr, &evalstr, &i, newstr);
		if (ft_isalpha(evalstr[i]) == 1 || (((ft_strstr(&evalstr[i], "++")
		== &evalstr[i]) || (ft_strstr(&evalstr[i], "--") == &evalstr[i])) &&
		ft_isalpha(evalstr[i + 2]) == 1))
		{
			if (zam_word_in_eval(&i, evalstr, newstr) == -1)
				return (NULL);
		}
		else
			ft_strcat_char(newstr, evalstr[i++]);
	}
	ft_strdel(&evalstr);
	return (newstr);
}
