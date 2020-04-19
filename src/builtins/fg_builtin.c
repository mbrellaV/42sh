/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:23:18 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
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
		continue_job(get_job_by_number(ft_atoi(mas[1])), 1);
	}
	else
		return (-1);
	return (0);
}
