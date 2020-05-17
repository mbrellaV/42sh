#include "eval_expr.h"

int		issc(char c)
{
	return (c == '(' || c == ')');
}

int		opr_znak(char *dstr)
{
	int		i;
	int		sum;
	char	*str;

	i = 0;
	str = dstr;
	sum = 300;
	if (issc(str[i]))
	{
		sum += str[i];
		return (sum);
	}
	while (str[i] && (is_znak(str[i]) || issc(str[i])))
	{
		sum += str[i];
		i++;
	}
	return (sum);
}

int		opr_znak_dop(char *dstr, int *marker)
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