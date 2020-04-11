/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:19:45 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/11 19:19:46 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_dop_str		*cr_dop_str_par1(t_lextoken *tmp1)
{
	t_dop_str	*t;

	if (tmp1 == NULL)
		return (NULL);
	if (!(t = ft_memalloc(sizeof(t_dop_str))))
		return (NULL);
	t->dopi_a = 0;
	t->dop_a = tmp1;
	t->f_a = 0;
	while (tmp1 != NULL && !is_cmd_delim(tmp1->operator_type))
	{
		if (tmp1->is_near_opt == 1)
			t->dopi_a++;
		if (tmp1->is_near_opt == 0)
			t->f_a++;
		tmp1 = tmp1->next;
	}
	if (!(t->tmp1_a = ft_memalloc(sizeof(t_exectoken))))
		return (NULL);
	if (t->dopi_a != 0 && !(t->tmp1_a->file_opt =
			(char**)ft_memalloc((t->dopi_a + 1) * sizeof(char *))))
		return (NULL);
	return (t);
}

t_exectoken		*do_parser_dop(t_dop_str *t, t_lextoken *tmp)
{
	if (tmp == NULL)
		return (NULL);
	if ((tmp->operator_type >= 3 && tmp->operator_type <= 10) ||
		tmp->operator_type == -2)
		t->prev_c = ft_cr_new_exectoken(tmp, NULL, -2, t);
	else
	{
		if (!(t->prev_c = ft_memalloc(sizeof(t_exectoken))))
			return (NULL);
		t->prev_c->file_args = NULL;
		t->prev_c->file_opt = NULL;
		t->prev_c->left = NULL;
		t->prev_c->right = NULL;
	}
	if (t->prev_c == NULL)
		return (NULL);
	t->start_c = t->prev_c;
	t->prevdot_c = t->prev_c;
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
		tmp = tmp->next;
	if (tmp == NULL)
		return (t->start_c);
	return (t->prev_c);
}

t_exectoken		*do_parser(t_lextoken *tmp)
{
	t_dop_str	*t;

	if (!(t = cr_dop_str_par()) ||
	!(t->prev_c = do_parser_dop(t, tmp)))
		ft_error_q(5);
	while (tmp != NULL)
	{
		if (is_cmd_delim(tmp->operator_type))
			t->i_c = tmp->operator_type;
		else if (t->i_c != -1)
		{
			if (t->i_c == 2)
				if (!(t->prev_c = ft_cr_new_exectoken(tmp,
						t->prev_c, t->i_c, t)))
					return (NULL);
			if ((t->i_c == 1 || t->i_c >= 9) && (t->prevdot_c =
					ft_cr_new_exectoken(tmp, t->prevdot_c, t->i_c, t)))
				t->prev_c = t->prevdot_c;
			t->i_c = -1;
		}
		tmp = tmp->next;
	}
	return (ft_kill_str_dop_exec(t, t->start_c));
}
