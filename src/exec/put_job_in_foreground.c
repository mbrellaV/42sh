/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_foreground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:11:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(globals()->g_shell_terminal, j->pgid);
	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(globals()->fd[2], "SIGCONT ERROR");
	}
	wait_for_job(j);
	tcsetpgrp(globals()->g_shell_terminal, globals()->g_shell_pgid);
	reset_input_mode();
}
