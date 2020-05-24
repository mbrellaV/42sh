/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inftopost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:26:44 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/04 13:44:12 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fshell.h>

int		main_calc(t_calc_token *tmp_token, int *error, t_int *l)
{
	while (tmp_token != NULL && tmp_token->type != CALC_END)
	{
		if (tmp_token->type == CALC_VAR)
			zam_var(tmp_token, error);
		if (*error == 0 && (tmp_token->type == CALC_NUMBER ||
		tmp_token->type == CALC_VAR))
		{
			addos(l->stackos, ft_atoi(tmp_token->var), l);
		}
		else if (*error == 0 && is_znak_type(tmp_token->type))
		{
			if ((dostack(l->stackos, l->stackzn, tmp_token, l)) == -1)
				return (return_with_error(NULL, error, NULL, l));
		}
		if (*error != 0)
			return (return_with_error(NULL, error, NULL, l));
		tmp_token = tmp_token->next;
	}
	return (calcend(&l->stackos, &l->stackzn, &l, error));
}

int		eval_expr(char *s, int *error, char *rec_var)
{
	t_int			*l;
	t_calc_token	*tmp_token;

	if (!(l = cr_new_el(s, error)))
		return (c_e((t_calc){NULL, NULL, NULL, error, NULL}));
	tmp_token = ft_eval_parse(s, rec_var);
	l->first_token = tmp_token;
	if (get_last_token(tmp_token)->type == CALC_ERROR ||
	get_last_token(tmp_token)->type == CALC_REC_ERROR)
		return (return_with_error(get_last_token(tmp_token), error, s, l));
	return (main_calc(tmp_token, error, l));
}
