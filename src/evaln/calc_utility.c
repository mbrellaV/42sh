#include "fshell.h"

void		free_calc_tokens(t_calc_token *tmp)
{
	t_calc_token	*dop;

	while (tmp != NULL)
	{
		ft_strdel(&tmp->var);
		dop = tmp;
		tmp = tmp->next;
		free(dop);
	}
}

int			return_with_error(t_calc_token *error_token, int *error, char *all_str, t_int *l)
{
	*error = 1;
	if (error_token != NULL && all_str != NULL)
		ft_dprintf(2, "42sh: %s: syntax error in expression (error token is \"%s\")", all_str, error_token->var);
	if (l != NULL)
		free_calc_tokens(l->first_token);
	if (l != NULL)
	{
		free(l->stackos);
		free(l->stackzn);
		free(l);
	}
	return (0);
}

int		is_znak_type(t_calc_tkntype type)
{
	return ((type > CALC_NUMBER && type <= CALC_SEC_SC) && type != CALC_VAR &&
			type != CALC_INC && type != CALC_DEC && type != CALC_PRE_INC && type != CALC_PRE_DEC);
}

t_calc_token		*get_last_token(t_calc_token *tmp)
{
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}