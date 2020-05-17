#include "eval_expr.h"

int					is_incr_sym(char c)
{
	return (c == '+' || c == '-');
}

int			calc_word_size(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_incr_sym(str[i]))
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (i);
		i++;
	}
	if ((str[i] == '+' && str[i + 1] == '-') ||
		(str[i] == '-' && str[i + 1] == '+'))
		return (i);
	if (is_incr_sym(str[i]) && is_incr_sym(str[i + 1]))
		return (i + 2);
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