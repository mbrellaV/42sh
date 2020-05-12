/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operating_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:30:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_job			*find_job(pid_t pgid)
{
	t_job		*j;

	j = globals()->g_f_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

int				job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int				job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int				num_of_the_job(t_job *j)
{
	t_job		*job;
	int			num;

	job = globals()->g_f_job;
	num = 0;
	while (job)
	{
		if (job == j)
			return (num + 1);
		job = job->next;
		num++;
	}
	return (-1);
}
