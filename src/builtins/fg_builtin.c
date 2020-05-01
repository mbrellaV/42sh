/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:23:18 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
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
		if (ft_strcmp(mas[1], "%") == 0 || ft_strcmp(mas[1], "%%") == 0)
			continue_job(get_last_job(), 1);
		else if (ft_str_is_numeric(mas[1]))
			continue_job(get_job_by_number(ft_atoi(mas[1])), 1);
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
