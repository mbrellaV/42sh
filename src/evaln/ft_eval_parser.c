#include "fshell.h"

int					is_incr(t_calc_tkntype type)
{
	return (type == CALC_PRE_INC || type == CALC_PRE_DEC || type == CALC_INC || type == CALC_DEC);
}



t_calc_token		*ft_make_token_from_str(char *str, int *i, t_calc_token *prev_token)
{
	t_calc_token	*tmp_token;

	if ((tmp_token = check_and_define_pre_incr(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_calc_incr_after(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_calc_error(str, i, prev_token)))
		return (tmp_token);
	else if ((tmp_token = check_if_incr_with_num(str, i, prev_token)))
		return (tmp_token);
	else
	{
		return (define_standart_token(str, i));
	}
}

t_calc_token		*ft_eval_parse(char *str, char *rec_var)
{
	int				i;
	t_calc_token	*first_token;
	t_calc_token	*tmp_token;

	i = 0;
	tmp_token = NULL;
	if (!(first_token = ft_cr_new_calc_token(NULL, CALC_START)))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			tmp_token = ft_make_token_from_str(&str[i], &i, tmp_token);
			if (tmp_token)
			{
				add_token_cr(first_token, tmp_token);
			}
			if (tmp_token && tmp_token->type == CALC_ERROR)
			{
				return (first_token);
			}
			if (tmp_token && rec_var && !ft_strcmp(tmp_token->var, rec_var))
			{
				add_token_cr(first_token, ft_cr_new_calc_token(tmp_token->var, CALC_REC_ERROR));
				return (first_token);
			}
		}
		else
			i++;
	}
	return (first_token);
}

