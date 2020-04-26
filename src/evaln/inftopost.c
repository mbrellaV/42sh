/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inftopost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:26:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

int		opr_znak(char *dstr, int *marker)
{
	int		i;
	int		sum;
	char	*str;

	i = *marker;
	str = dstr;
	sum = 300;
	if (issc(str[i]))
	{
		sum += str[i];
		(*marker)++;
		return (sum);
	}
	while (str[i] && (is_znak(str[i]) || issc(str[i])))
	{
		sum += str[i];
		(*marker)++;
		i++;
	}
	return (sum);
}

int		check_calc_str(char *str)
{
	char	*dopstr;

	if (str == NULL)
		return (-1);
	if (word_size(str) < 0)
		return (-1);
	dopstr = ft_strsub(str, 0, word_size(str));
	if ((ft_strstr(dopstr, "+++") != NULL ||
			ft_strstr(dopstr, "---") != NULL ||
			ft_strstr(dopstr, ">>>") != NULL ||
			ft_strstr(dopstr, "<<<") != NULL ||
			ft_strstr(dopstr, "&&&") != NULL ||
			ft_strstr(dopstr, "|||") != NULL ||
			ft_strstr(dopstr, "**") != NULL ||
			ft_strstr(dopstr, "//") != NULL))
	{
		ft_strdel(&dopstr);
		return (-1);
	}
	ft_strdel(&dopstr);
	return (1);
}

int		calc_error(int *stackos, int *stackzn, t_int *str, int *error, char *delstr)
{
	free(stackos);
	free(stackzn);
	free(str);
	ft_strdel(&delstr);
	*error = 1;
	return (-1);
}

char			*do_save_var(char *str)
{
	char	*dopstr;
	int		i;
	char	*str_for_rec;
	int		dopi;
	char	*str_from_env;

	i = 0;
	dopi = 0;
	if (check_calc_str(str) == -1)
		return (NULL);
	i += word_size(str);
	if (str[i - 1] == '+')
		dopstr = ft_strdup("0+");
	else if (str[i - 1] == '-')
		dopstr = ft_strdup("0-");
	else
		dopstr = ft_strdup("0");
	if ((str[i - 1] == '-' || str[i - 2] == '-'))
		dopi = -1;
	if ((str[i - 1] == '+' && str[i - 2] == '+'))
		dopi = 1;
	if (dopi != 0)
	{
		str_for_rec = ft_strsub(str, 0, i - 2);
		if (!(str_from_env = ft_get_var(str_for_rec, globals()->g_all_var)))
			i = 0;
		else
			i = ft_atoi(str_from_env);
		ft_strdel(&dopstr);
		ft_strdel(&str_from_env);
		dopstr = ft_itoa(i + dopi);
		set_new_var(str_for_rec, dopstr, &globals()->g_all_var);
		set_new_var(str_for_rec, dopstr, &globals()->g_env);
		ft_strdel(&str_for_rec);
	}
	ft_strdel(&str);
	return (dopstr);
}

char			*change_vars(char *evalstr)
{
	int		i;
	char	*dopstr;
	char	*newstr;
	char	*str_for_del;

	i = 0;
	if (!(newstr = ft_memalloc(130000)))
		return (NULL);
	while (evalstr[i] != '\0')
	{
		if (ft_isalpha(evalstr[i]) == 1)
		{
			dopstr = ft_strsub(evalstr, i, word_size(&evalstr[i]));
			str_for_del = dopstr;
			if (!(dopstr = do_save_var(dopstr)))
			{
				ft_strdel(&evalstr);
				ft_strdel(&newstr);
				ft_strdel(&str_for_del);
				return (NULL);
			}
			ft_strcat(newstr, dopstr);
			evalstr = do_zam_str_by_str(i, word_size(&evalstr[i]), evalstr, dopstr);
			i += word_size(&evalstr[i]);
		}
		else
		{
			dopstr = ft_strdup(" ");
			dopstr[0] = evalstr[i];
			ft_strcat(newstr, dopstr);
			ft_strdel(&dopstr);
			i++;
		}
	}
	ft_strdel(&evalstr);
	return (newstr);
}

int		eval_expr(char *s, int *error)
{
	int		*stackos;
	int		*stackzn;
	t_int	*l;
	int		i;
	int		last_token;

	i = 0;
	last_token = 0;
	if (!(s = change_vars(s)))
		return ((*error = 1));
	l = cr_new_el();
	if (!(stackos = (int*)ft_memalloc(4 * ft_strlen(s))))
		return (-1);
	if (!(stackzn = (int*)ft_memalloc(4 * ft_strlen(s))))
		return (-1);
	while (i < ft_strlen(s) && s[i] != '\0')
	{
		if (check_calc_str(&s[i]) == -1)
			return (calc_error(stackos, stackzn, l, error, s));
		if ((s[i] >= '0' && s[i] <= '9') || ((s[i] == '-' || s[i] == '+') &&
		s[i + 1] != '\0' && (s[i + 1] >= '0' && s[i + 1] <= '9') && l->i == 1))
		{
			if (last_token == 1)
				return (calc_error(stackos, stackzn, l, error, s));
			last_token = 1;
			addos(stackos, ft_atoi_with(s + i, &i), l);
			l->i = 0;
		}
		if ((is_znak(s[i]) && l->i == 0) || (s[i] == '(' || s[i] == ')'))
		{
			if (last_token == 3)
				return (calc_error(stackos, stackzn, l, error, s));
			if (last_token != 0)
				last_token++;
			dostack(stackos, stackzn, opr_znak(s, &i), l);
		}
		else
			i++;
	}
	ft_strdel(&s);
	return (calcend(&stackos, &stackzn, &l));
}
