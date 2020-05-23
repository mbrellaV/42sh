#include "eval_expr.h"

int					is_incr_sym(char c)
{
	return (c == '+' || c == '-');
}

int			var_size(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalpha(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int			num_size(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int			znak_size(char *str)
{

	int		i;

	i = 0;
	if (issc(str[i]))
	{
		i++;
		return (i);
	}
	while (str[i] && (is_znak(str[i]) && !issc(str[i])) && i < 2)
	{
		i++;
	}
	return (i);
}

//int			ft_num_with_sym(char *str)
//{
//	int		i;
//
//	i = 1;
//	if (is_incr_sym(str[i]))
//		return (1);
//	while (str[i] && (str[i] == ' '))
//	{
//		i++;
//	}
//	if ()
//	ft_atoi_with(str + i, &i);
//	return (i);
//}

int			calc_word_size(char *str, int type)
{
	int		i;

	i = 0;
//	if (type == 1)
//		return (ft_num_with_sym(str));
	if (ft_isalpha(*str))
		return (var_size(str));
	if (ft_isdigit(*str))
		return (num_size(str));
	if (is_znak(*str))
		return (znak_size(str));
	if ((*str > 31 && *str < 127))
		return (1);
	return (i);
}

//int			calc_word_size(char *str)
//{
//	int		i;
//
//	i = 0;
//	while (str[i] != '\0')
//	{
//		if (is_incr_sym(str[i]))
//			break ;
//		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
//			return (i);
//		i++;
//	}
//	if ((str[i] == '+' && str[i + 1] == '-') ||
//		(str[i] == '-' && str[i + 1] == '+'))
//		return (i);
//	if (is_incr_sym(str[i]) && is_incr_sym(str[i + 1]))
//		return (i + 2);
//	return (i);
//}