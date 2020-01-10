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
	return (i == 1 || i == 2);
}

t_dop_str_for_cr_new	*cr_dop_str_par1(t_lextoken *tmp1)
{
	t_dop_str_for_cr_new	*t;

	if (tmp1 == NULL)
		return (NULL);
	if (!(t = ft_memalloc(sizeof(t_dop_str_for_cr_new))))
		return (NULL);
	t->dopi = 0;
	t->dop = tmp1;
	t->f = 0;
	while (tmp1 != NULL && !is_cmd_delim(tmp1->operator_type))
	{
		if (tmp1->is_near_opt == 1)
			t->dopi++;
		if (tmp1->is_near_opt == 0)
			t->f++;
		tmp1 = tmp1->next;
	}
	if (!(t->tmp1 = ft_memalloc(sizeof(t_exectoken))))
		return (NULL);
	if (t->dopi != 0 && !(t->tmp1->file_opt =
			(char**)ft_memalloc((t->dopi + 1) * sizeof(char *))))
		return (NULL);
	return (t);
}

void					dop_cr_new_exec(t_dop_str_for_cr_new *t,
		t_exectoken *prev, int op_type, int type)
{
	if (type == 0)
	{
		if (!(t->tmp1->file_args =
				(char**)ft_memalloc((t->f + 1) * sizeof(char *))))
			return ;
		t->tmp1->left = NULL;
		t->tmp1->right = NULL;
		t->dopi = 0;
		t->f = 0;
		if (prev != NULL)
		{
			if (op_type == get_op_type("|"))
				prev->left = t->tmp1;
			else if (op_type == get_op_type(";"))
				prev->right = t->tmp1;
		}
		return ;
	}
	t->tmp1->file_args[t->f] = NULL;
	if (t->dopi != 0)
		t->tmp1->file_opt[t->dopi] = NULL;
	if (t->dopi == 0)
		t->tmp1->file_opt = NULL;
}

t_exectoken				*ft_cr_new_exectoken(t_lextoken *tmp,
												t_exectoken *prev, int op_type)
{
	t_dop_str_for_cr_new *t;

	if (!(t = cr_dop_str_par1(tmp)))
		return (NULL);
	dop_cr_new_exec(t, prev, op_type, 0);
	while (t->dop != NULL && !is_cmd_delim(t->dop->operator_type))
	{
		if (t->dop->is_near_opt == 0)
		{
			if (!(t->tmp1->file_args[t->f] = ft_strsub(t->dop->line,
					0, ft_strlen(t->dop->line))))
				return (ft_zach(NULL, t));
			t->f++;
		}
		else if (t->dop->is_near_opt == 1)
		{
			if (!(t->tmp1->file_opt[t->dopi] = ft_strsub(t->dop->line,
					0, ft_strlen(t->dop->line))))
				return (ft_zach(NULL, t));
			t->dopi++;
		}
		t->dop = t->dop->next;
	}
	dop_cr_new_exec(t, prev, op_type, 1);
	return (ft_zach(t->tmp1, t));
}

t_dop_str				*cr_dop_str_par(void)
{
	t_dop_str	*t;

	if (!(t = ft_memalloc(sizeof(t_dop_str))))
		return (NULL);
	t->tmp = NULL;
	t->dop = 0;
	t->d = 0;
	t->i = 0;
	t->doptail = NULL;
	t->tail = NULL;
	t->prev = NULL;
	t->prevdot = NULL;
	t->start = NULL;
	return (t);
}
