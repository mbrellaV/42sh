/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuing_stopped_jobs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:19:34 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

/* Mark a stopped job J as being running again.  */

void	mark_job_as_running (t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		p->stopped = 0;
	j->notified = 0;
}

/* Continue the job J.  */

void	continue_job (t_job *j, int foreground)
{
	if (j == NULL)
	{
		return ;
	}
	mark_job_as_running(j);
	if (foreground)
	{
		put_job_in_foreground(j, 1);
	}
	else
	{
		put_job_in_background(j, 1);
	}

}