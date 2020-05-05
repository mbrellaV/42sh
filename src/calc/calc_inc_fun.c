#include "calc.h"

t_calc_tkn	*calc_get_inc_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = (*str == '+') ? CALC_INC : CALC_DEC;
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 2;
	return (token);
}
