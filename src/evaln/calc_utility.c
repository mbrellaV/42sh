/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void			free_calc_tokens(t_calc_token *tmp)
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

int				return_with_error(t_calc_token *error_token, int *error,
		char *all_str, t_int *l)
{
	*error = 1;
	if (error_token != NULL && all_str != NULL &&
	error_token->type == CALC_ERROR)
		ft_dprintf(globals()->fd[2],
				"42sh: %s: error in expression (error token is \"%s\")\n",
				all_str, error_token->var);
	else if (error_token != NULL && all_str != NULL &&
	error_token->type == CALC_REC_ERROR)
		ft_dprintf(globals()->fd[2],
				"42sh: %s: expression level exceeded (error token is %s)\n",
				all_str, error_token->var);
	else if (error_token != NULL && all_str != NULL &&
	error_token->type == CALC_NUM_OVERFLOW_ERROR)
		ft_dprintf(globals()->fd[2],
				"42sh: %s: number is too big (error token is %s)\n",
				all_str, error_token->var);
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

int				is_znak_type(t_calc_tkntype type)
{
	return ((type > CALC_NUMBER && type <= CALC_SEC_SC) && type != CALC_VAR &&
			type != CALC_INC && type != CALC_DEC &&
			type != CALC_PRE_INC && type != CALC_PRE_DEC);
}

t_calc_token	*get_last_token(t_calc_token *tmp)
{
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
