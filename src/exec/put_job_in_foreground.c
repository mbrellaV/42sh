/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_foreground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:11:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/16 13:36:48 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(g_shell_terminal, j->pgid);
	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	wait_for_job(j);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
}
