/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 12:44:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/16 10:22:07 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_job		*get_job_by_number(int n)
{
	t_job	*j;
	int		i;

	j = g_f_job;
	if (n < 0)
		return (NULL);
	i = 1;
	while (j && i < n)
	{
		i++;
		j = j->next;
	}
	return (j);
}

t_job		*get_last_job(void)
{
	t_job	*j;

	j = g_f_job;
	while (j && j->next)
	{
		j = j->next;
	}
	return (j);
}
