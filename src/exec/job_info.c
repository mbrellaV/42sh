/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:46:42 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/16 10:42:29 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		format_job_info(t_job *j, const char *status, int num)
{
	ft_dprintf(2, "[%d] + %ld (%s): %s\n", num,
			(long)j->pgid, status, j->command);
}

static void	norme_help(t_del *del)
{
	format_job_info(del->j, "completed", del->d);
	if (del->jlast)
		del->jlast->next = del->jnext;
	else
		g_f_job = del->jnext;
}

void		do_job_notification(void)
{
	t_del	del;

	del.d = 0;
	update_status();
	del.jlast = NULL;
	del.j = g_f_job;
	while (del.j)
	{
		del.d++;
		del.jnext = del.j->next;
		if (job_is_completed(del.j))
			norme_help(&del);
		else if (job_is_stopped(del.j) && !del.j->notified)
		{
			format_job_info(del.j, "suspended", del.d);
			del.j->notified = 1;
			del.jlast = del.j;
		}
		else
			del.jlast = del.j;
		del.j = del.j->next;
	}
}
