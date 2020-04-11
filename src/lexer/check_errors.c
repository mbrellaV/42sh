/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:45:44 by plettie           #+#    #+#             */
/*   Updated: 2020/02/06 11:45:52 by plettie          ###   ########.fr       */
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
