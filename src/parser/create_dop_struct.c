/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dop_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:54:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/14 18:54:27 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

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

t_dop_str				*cr_dop_str_par1(t_lextoken *tmp1)
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
