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

#include "eval_expr.h"

//t_int	*eval_help(t_int *l)
//{
//	if ((is_znak(l->s[l->i]) && (l->last_token++) && l->d == 0) ||
//		(l->s[l->i] == '(' || l->s[l->i] == ')'))
//		dostack(l->stackos, l->stackzn, opr_znak(l->s, &l->i), l);
//	else
//		l->i++;
//	return (l);
//}

int		eval_expr(char *s, int *error)
{
//	t_int			*l;
	t_calc_token	*first_token;
//
//	if (!(l = cr_new_el(s, error)))
//		return (c_e((t_calc){NULL, NULL, NULL, error, NULL}));
	first_token = ft_eval_parse(s);
	while (first_token != NULL)
	{
		dprintf(2, "\n|%s, %d|\n", first_token->var, first_token->type);
		first_token = first_token->next;
	}
	return (0);
//	while (l->i < (int)ft_strlen(l->s) && l->s[l->i] != '\0')
//	{
//		if (check_calc_str(&l->s[l->i]) == -1)
//			return (c_e((t_calc){l->stackos, l->stackzn, l, error, l->s}));
//		if ((l->s[l->i] >= '0' && l->s[l->i] <= '9') ||
//		((l->s[l->i] == '-' || l->s[l->i] == '+') && l->s[l->i + 1] != '\0' &&
//		(l->s[l->i + 1] >= '0' && l->s[l->i + 1] <= '9') && l->d == 1))
//		{
//			if (l->last_token == 1)
//				return (c_e((t_calc){l->stackos, l->stackzn, l, error, l->s}));
//			l->last_token = 1;
//			addos(l->stackos, ft_atoi_with(l->s + l->i, &l->i), l);
//			l->d = 0;
//		}
//		l = eval_help(l);
//		if (l->last_token >= 3)
//			return (c_e((t_calc){l->stackos, l->stackzn, l, error, l->s}));
//	}
//	ft_strdel(&l->s);
//	return (calcend(&l->stackos, &l->stackzn, &l));
}
