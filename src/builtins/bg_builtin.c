/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:23:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		do_bg(char **mas)
{
	if (mas[0] != NULL && mas[1] == NULL)
	{
		continue_job(get_last_job(), 0);
	}
	else if (mas[0] != NULL && mas[1] != NULL && mas[2] == NULL)
	{
		if (mas[1][0] == '%')
		{
			if (mas[1][1] == '%' || mas[1][1] == '+')
				continue_job(get_last_job(), 0);
			else if (mas[1][1] == '-')
				continue_job(get_prev_last_job(), 0);
			else if (ft_isdigit(mas[1][1]))
				continue_job(get_job_by_number(ft_atoi(mas[1])), 0);
			else if (isword(mas[1][1]) == 1)
				continue_job(get_job_by_start_str(&mas[1][1]), 0);
			else if (isword(mas[1][1]) == 1)
				continue_job(get_job_by_cont_str(&mas[1][1]), 0);
		}
	}
	else
		return (-1);
	return (0);
}
