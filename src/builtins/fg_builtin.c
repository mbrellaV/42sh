/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:23:18 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		do_fg(char **mas)
{
	if (mas[0] != NULL && mas[1] == NULL)
	{
		continue_job(get_last_job(), 1);
	}
	else if (mas[0] != NULL && mas[1] != NULL && mas[2] == NULL)
	{
		if (mas[1][0] == '%')
		{
			if (mas[1][1] == '%' || mas[1][1] == '+')
				continue_job(get_last_job(), 1);
			else if (mas[1][1] == '-')
				continue_job(get_prev_last_job(), 1);
			else if (ft_isdigit(mas[1][1]))
				continue_job(get_job_by_number(ft_atoi(mas[1])), 1);
			else if (isword(mas[1][1]) == 1)
				continue_job(get_job_by_start_str(&mas[1][1]), 1);
			else if (isword(mas[1][1]) == 1)
				continue_job(get_job_by_cont_str(&mas[1][1]), 1);
		}
		else
		{
			ft_dprintf(globals()->fd[2], "42sh: fg: %s: no such job", mas[1]);
			return (-1);
		}
	}
	else
	{
		ft_dprintf(globals()->fd[2], "usage: fg [job_id]\n");
		return (-1);
	}
	return (0);
}
