/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:13:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void				put_job_in_background(t_job *j, int cont)
{
	struct timespec	tw;
	struct timespec	tr;

	tw = (struct timespec){0, 22000000};
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(globals()->fd[2], "kill (SIGCONT)");
	nanosleep(&tw, &tr);
}
