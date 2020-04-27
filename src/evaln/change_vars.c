#include "eval_expr.h"

char			*save_to_env(char *str, int i, char *dopstr)
{
	char	*str_for_rec;
	int		dopi;
	char	*str_from_env;

	dopi = 0;
	if ((str[i - 1] == '-' || str[i - 2] == '-'))
		dopi = -1;
	if ((str[i - 1] == '+' && str[i - 2] == '+'))
		dopi = 1;
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
	ft_strdel(&str);
	return (dopstr);
}

char			*do_save_var(char *str)
{
	char	*dopstr;
	int		i;

	i = 0;
	if (check_calc_str(str) == -1)
		return (NULL);
	i += word_size(str);
	if (str[i - 1] == '+')
		dopstr = ft_strdup("0+");
	else if (str[i - 1] == '-')
		dopstr = ft_strdup("0-");
	else
	{
		if (!(dopstr = ft_get_var(str, globals()->g_all_var)))
			return (ft_strdup("0"));
		else
			return (dopstr);
	}
	return (save_to_env(str, i, dopstr));
}

int				zam_word_in_eval(int *i, char *evalstr, char *newstr)
{
	char	*dopstr;
	char	*str_for_del;

	dopstr = ft_strsub(evalstr, *i, word_size(&evalstr[*i]));
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
	*i += word_size(&evalstr[*i]);
	return (1);
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
		if (ft_isalpha(evalstr[i]) == 1)
		{
			if (zam_word_in_eval(&i, evalstr, newstr) == -1)
				return (NULL);
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