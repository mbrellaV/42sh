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

//t_int	*eval_help(t_int *l)
//{
//	if ((is_znak(l->s[l->i]) && (l->last_token++) && l->d == 0) ||
//		(l->s[l->i] == '(' || l->s[l->i] == ')'))
//		dostack(l->stackos, l->stackzn, opr_znak(l->s, &l->i), l);
//	else
//		l->i++;
//	return (l);
//}

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
		//dprintf(2, "\nroflan: |%s, %d, %d|\n", env_var, res, *error);
		if (*error != 0)
			return ;
	}
	res += dop;
	str_to_del = var_token->var;
	var_token->var = ft_itoa(res);
	//dprintf(2, "\nrdadadadad: |%s, %d, %d, %s|\n", env_var, res, *error, var_token->var);
	if (var_token->next && var_token->next->type == CALC_INC)
		res++;
	if (var_token->next && var_token->next->type == CALC_DEC)
		res--;
	dop_str = ft_itoa(res);
	if ((var_token->prev && (var_token->prev->type == CALC_PRE_DEC || var_token->prev->type == CALC_PRE_INC)) ||
			(var_token->next && (var_token->next->type == CALC_INC || var_token->next->type == CALC_DEC)))
		set_new_var(str_to_del, dop_str, &globals()->g_all_var);
	//dprintf(2, "\nroflan1: |%s, %s, %s|\n", str_to_del, dop_str, var_token->var);
	ft_strdel(&dop_str);
	ft_strdel(&str_to_del);
}

int		is_znak_type(t_calc_tkntype type)
{
	return ((type > CALC_NUMBER && type < CALC_SEC_SC) && type != CALC_VAR &&
	type != CALC_INC && type != CALC_DEC && type != CALC_PRE_INC && type != CALC_PRE_DEC);
}

int		eval_expr(char *s, int *error)
{
	t_int			*l;
	t_calc_token	*tmp_token;
	t_calc_token	*first_token;
	int				i = 0;

	if (!(l = cr_new_el(s, error)))
		return (c_e((t_calc){NULL, NULL, NULL, error, NULL}));
	tmp_token = ft_eval_parse(s);
	first_token = tmp_token;
	while (tmp_token != NULL && tmp_token->type != CALC_END)
	{
		//dprintf(2, "\n|%s, %d|\n", tmp_token->var, tmp_token->type);
		if (tmp_token->type == CALC_VAR)
			zam_var(tmp_token, error);
		if (*error == 0 && (tmp_token->type == CALC_NUMBER || tmp_token->type == CALC_VAR))
		{
			//dprintf(2, "\nddd: |%s|\n", tmp_token->var);
			addos(l->stackos, ft_atoi(tmp_token->var), l);
		}
		else if (*error == 0 && is_znak_type(tmp_token->type))
		{
			//dprintf(2, "\nsss: ||\n");
			dostack(l->stackos, l->stackzn, tmp_token->type, l);
		}
//		while (*error == 0 && i <= l->zl)
//		{
//			dprintf(2, "\nsas: |%d|\n", l->stackos[i]);
//			i++;
//		}
		if (*error != 0)
			return (0);
		tmp_token = tmp_token->next;
	}
	free_calc_tokens(first_token);
	return (calcend(&l->stackos, &l->stackzn, &l));
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
