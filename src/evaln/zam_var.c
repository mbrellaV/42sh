#include "fshell.h"

void		zam_var(t_calc_token *var_token, int *error)
{
	char	*env_var;
	int		dop;
	int		res;
	char	*str_to_del;
	char	*dop_str;

	res = 0;
	dop = 0;
	if (var_token->prev && var_token->prev->type == CALC_PRE_DEC)
		dop--;
	if (var_token->prev && var_token->prev->type == CALC_PRE_INC)
		dop++;
	if ((env_var = ft_get_var(var_token->var, globals()->g_all_var)))
	{
		res = eval_expr(env_var, error);
		ft_strdel(&env_var);
		if (*error != 0)
			return ;
	}
	res += dop;
	str_to_del = var_token->var;
	var_token->var = ft_itoa(res);
	if (var_token->next && var_token->next->type == CALC_INC)
		res++;
	if (var_token->next && var_token->next->type == CALC_DEC)
		res--;
	dop_str = ft_itoa(res);
	if ((var_token->prev && (var_token->prev->type == CALC_PRE_DEC || var_token->prev->type == CALC_PRE_INC)) ||
		(var_token->next && (var_token->next->type == CALC_INC || var_token->next->type == CALC_DEC)))
		set_new_var(str_to_del, dop_str, &globals()->g_all_var);
	ft_strdel(&dop_str);
	ft_strdel(&str_to_del);
}