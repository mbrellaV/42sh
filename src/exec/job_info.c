/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:46:42 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
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

static int	job_checker(t_job *j, int d, char *str)
{
	if (format_job_info(j, str, d) == 1)
		return (1);
	return (0);
}

int			do_job_notification(void)
{
	t_job	*j;
	int		d;
	int		stat;

	update_status();
	d = 0;
	j = globals()->g_f_job;
	stat = 0;
	while (j && d++)
	{
		if (job_is_completed(j))
			stat = job_checker(j, d, "completed");
		else if (job_is_stopped(j))
			stat = job_checker(j, d, "suspended");
		else if (j->foreground == 0)
			stat = job_checker(j, d, "Running");
		if (stat == 1)
			return (1);
		j = j->next;
	}
	return (0);
}
