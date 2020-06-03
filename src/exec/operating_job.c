/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operating_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:30:33 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_exectoken		*get_last_pipe_tree(t_exectoken *tmp)
{
	while (tmp->left != NULL)
	{
		tmp = tmp->left;
	}
	return (tmp);
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
