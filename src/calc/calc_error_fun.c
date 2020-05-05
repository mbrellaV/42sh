#include "calc.h"

long long	calc_error(t_calc_err *error, t_calc_err_type type)
{
	if (!error)
		return (0);
	error->type = type;
	error->status = 1;
	return (0);
}
