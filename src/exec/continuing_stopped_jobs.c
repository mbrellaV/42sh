/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuing_stopped_jobs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:19:34 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/18 17:19:35 by qmartina         ###   ########.fr       */
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
	mark_job_as_running (j);
	if (foreground)
	{
		dprintf(2, "\n\n\n\\n\n\n\n\\n\n\n\\n\n\n\n\n\n\\n\nsas11111111111111\n");
		put_job_in_foreground (j, 1);
	}
	else
	{
		dprintf(2, "\n\n\n\\n\n\n\n\\n\n\n\\n\n\n\n\n\n\\n\nsas123222222222: ");

		put_job_in_background (j, 1);
	}

}