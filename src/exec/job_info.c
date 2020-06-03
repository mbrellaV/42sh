/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:46:42 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			format_job_info(t_job *j, const char *status, int num)
{
	if (!vivod(1))
		return (1);
	ft_dprintf(globals()->fd[1], "[%d] + %ld (%s): %s\n", num,
			(long)j->pgid, status, j->command);
	return (0);
}

static int	vivod_info(t_job *j, int d)
{
	if (job_is_completed(j))
	{
		if (format_job_info(j, "completed", d) == 1)
			return (1);
	}
	else if (job_is_stopped(j))
	{
		if (format_job_info(j, "suspended", d) == 1)
			return (1);
	}
	else if (j->foreground == 0)
	{
		if (format_job_info(j, "Running", d) == 1)
			return (1);
	}
	return (0);
}

int			do_job_notification(void)
{
	t_job	*j;
	int		d;

	update_status();
	d = 0;
	j = globals()->g_f_job;
	while (j)
	{
		d++;
		if (vivod_info(j, d))
			return (1);
		j = j->next;
	}
	return (0);
}
