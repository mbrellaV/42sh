/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

long long		calc(char *str, t_calc_err *error)
{
	t_calc_tkns	*s_tokens;
	long long	res;

	if (!str || !error)
		return (0);
	if (!(str = change_vars(str)))
	{
		error->status = 1;
		return (0);
	}
	if (!(s_tokens = calc_get_arr_tkns(str, NULL, 0)))
		return (calc_error(error, CALC_ERR_LX));
	res = calc_exp(s_tokens, 0, error);
	calc_del_tkns(s_tokens);
	ft_strdel(&str);
	return (res);
}

long long		calc_exp(t_calc_tkns *s_tokens, size_t index, t_calc_err *error)
{
	long long	result;

	if (!s_tokens || !calc_check_index(s_tokens, index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	if (s_tokens->tokens[index].type == CALC_END)
		return (0);
	result = calc_add_sub(s_tokens, &index, error);
	if (error->status)
		return (0);
	if (s_tokens->tokens[index].type != CALC_END)
	{
		if (s_tokens->tokens[index].type == CALC_RPARENT)
			return (calc_error(error, CALC_ERR_PARENT));
		return (calc_error(error, CALC_ERR_SYNTAX));
	}
	return (result);
}
