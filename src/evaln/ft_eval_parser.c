/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 13:41:58 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int					is_incr(t_calc_tkntype type)
{
	return (type == CALC_PRE_INC || type == CALC_PRE_DEC ||
	type == CALC_INC || type == CALC_DEC);
}

t_calc_token		*ft_make_token_from_str(char *str, int *i,
		t_calc_token *prev_token)
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
	t_calc_token	*f_token;
	t_calc_token	*ttok;

	i = 0;
	ttok = NULL;
	if (!(f_token = ft_ntoken(NULL, CALC_START)))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			ttok = ft_make_token_from_str(&str[i], &i, ttok);
		if (str[i] != ' ' && ttok)
			add_token_cr(f_token, ttok);
		if (str[i] != ' ' && ttok && ttok->type == CALC_ERROR)
			return (f_token);
		if (str[i] != ' ' && ttok && rec_var && !ft_strcmp(ttok->var, rec_var))
		{
			add_token_cr(f_token, ft_ntoken(ttok->var, CALC_REC_ERROR));
			return (f_token);
		}
		else
			i++;
	}
	return (f_token);
}
