#include "eval_expr.h"

int		calc_error(int *stackos, int *stackzn, t_int *str, int *error, char *delstr)
{
	if (stackos != NULL)
		free(stackos);
	if (stackzn != NULL)
		free(stackzn);
	if (str != NULL)
		free(str);
	ft_strdel(&delstr);
	*error = 1;
	return (-1);
}