#include "eval_expr.h"

int		check_calc_str(char *str)
{
	char	*dopstr;

	if (str == NULL)
		return (-1);
	if (word_size(str) < 0)
	{
		if (issc(*str))
			return (1);
		else
			return (-1);
	}
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

int		check_calc_sc(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			return (1);
		else if (str[i] == ')')
			return (0);
		i++;
	}
	return (1);
}