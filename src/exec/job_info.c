/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:46:42 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void		format_job_info(t_job *j, const char *status, int num)
{
	ft_dprintf(globals()->fd[2], "[%d] + %ld (%s): %s\n", num,
			(long)j->pgid, status, j->command);
}

void		do_job_notification(void)
{
	t_job	*j;
	int		d;

	update_status();
	d = 0;
	j = globals()->g_f_job;
	while (j)
	{
		d++;
		if (job_is_completed(j))
			format_job_info(j, "completed", d);
		else if (j->foreground == 0)
			format_job_info(j, "Running", d);
		else if (job_is_stopped(j))
			format_job_info(j, "suspended", d);
		j = j->next;
	}
}
