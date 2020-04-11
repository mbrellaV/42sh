/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:19:24 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 16:19:25 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int						is_cmd_delim(int i)
{
	return (i == 1 || i == 2 || i >= 9);
}

t_dop_str				*standart_t(t_dop_str *t, int op_type)
{
	t->tmp1_a->foreground = 1;
	t->tmp1_a->left = NULL;
	t->tmp1_a->right = NULL;
	t->tmp1_a->should_wait_and = 0;
	t->tmp1_a->should_wait_or = 0;
	if (op_type == 10)
		t->tmp1_a->should_wait_and = 1;
	if (op_type == 11)
		t->tmp1_a->should_wait_or = 1;
	t->dopi_a = 0;
	t->f_a = 0;
	return (t);
}

void					dop_cr_new_exec(t_dop_str *t,
		t_exectoken *prev, int op_type, int type)
{
	if (type == 0)
	{
		if (!(t->tmp1_a->file_args =
				(char**)ft_memalloc((t->f_a + 1) * sizeof(char *))))
			return ;
		t = standart_t(t, op_type);
		if (prev != NULL)
		{
			if (op_type == get_op_type("|"))
				prev->left = t->tmp1_a;
			else if (op_type == get_op_type(";") || op_type >= 9)
				prev->right = t->tmp1_a;
		}
		return ;
	}
	if (t->dop_a && t->dop_a->operator_type == 9)
		t->tmp1_a->foreground = 0;
	t->tmp1_a->file_args[t->f_a] = NULL;
	if (t->dopi_a != 0)
		t->tmp1_a->file_opt[t->dopi_a] = NULL;
	if (t->dopi_a == 0)
		t->tmp1_a->file_opt = NULL;
}

t_exectoken				*ft_cr_new_exectoken(t_lextoken *tmp,
		t_exectoken *prev, int op_type, t_dop_str *t)
{
	if (!(t = cr_dop_str_par1(tmp)))
		return (NULL);
	dop_cr_new_exec(t, prev, op_type, 0);
	while (t->dop_a != NULL && !is_cmd_delim(t->dop_a->operator_type))
	{
		if (t->dop_a->is_near_opt == 0)
		{
			if (!(t->tmp1_a->file_args[t->f_a] = ft_strdup(t->dop_a->line)))
				return (ft_kill_str_dop_exec(t, NULL));
			t->f_a++;
		}
		else if (t->dop_a->is_near_opt == 1)
		{
			if (!(t->tmp1_a->file_opt[t->dopi_a] = ft_strdup(t->dop_a->line)))
				return (ft_kill_str_dop_exec(t, NULL));
			t->dopi_a++;
		}
		t->dop_a = t->dop_a->next;
	}
	dop_cr_new_exec(t, prev, op_type, 1);
	return (ft_kill_str_dop_exec(t, t->tmp1_a));
}

t_dop_str				*cr_dop_str_par(void)
{
	t_dop_str	*t;

	if (!(t = ft_memalloc(sizeof(t_dop_str))))
		return (NULL);
	t->tmp_c = NULL;
	t->dop_c = 0;
	t->d_c = 0;
	t->i_c = 0;
	t->doptail_c = NULL;
	t->tail_c = NULL;
	t->prev_c = NULL;
	t->prevdot_c = NULL;
	t->start_c = NULL;
	return (t);
}
