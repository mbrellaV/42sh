/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 12:44:23 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_job		*get_job_by_number(int n)
{
	t_job	*j;
	int		i;

	j = globals()->g_f_job;
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

	j = globals()->g_f_job;
	while (j && j->next)
	{
		j = j->next;
	}
	return (j);
}

t_job		*get_prev_last_job(void)
{
	t_job	*j;

	j = globals()->g_f_job;
	while (j && j->next && j->next->next)
	{
		j = j->next;
	}
	return (j);
}

t_job		*get_job_by_start_str(char *str)
{
	t_job	*j;

	j = globals()->g_f_job;
	if (!str)
		return (NULL);
	while (j)
	{
		if (ft_strstr(j->command, str) == j->command + 1)
			return (j);
		j = j->next;
	}
	return (NULL);
}

t_job		*get_job_by_cont_str(char *str)
{
	t_job	*j;

	j = globals()->g_f_job;
	if (!str)
		return (NULL);
	while (j)
	{
		if (ft_strstr(j->command, str) != NULL)
			return (j);
		j = j->next;
	}
	return (NULL);
}
