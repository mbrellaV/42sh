/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:53:00 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/14 18:53:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int				check_all_errors(t_lextoken *tmp)
{
	while (tmp)
	{
		if (tmp->is_near_opt && tmp->line && get_op_type(tmp->line) >= 3 &&
			get_op_type(tmp->line) <= 8 && (tmp->next == NULL ||
			tmp->next->is_near_opt != 1))
		{
			return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}
