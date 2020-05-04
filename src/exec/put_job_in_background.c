/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:13:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:10 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void				put_job_in_background(t_job *j, int cont)
{
	struct timespec	tw;
	struct timespec	tr;

	tw = (struct timespec){0, 25000000};
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	nanosleep(&tw, &tr);
}
