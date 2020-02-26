/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:13:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/18 17:13:05 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void put_job_in_background (t_job *j, int cont) {
	/* Send the job a continue signal, if necessary.  */
	struct timespec tw = {0, 25000000};
	//Структура, в которую будет помещен остаток времени
	//задержки, если задержка будет прервана досрочно
	struct timespec tr;
	//dprintf(2, "\nground: |%d|\n", j->first_process->foreground);
	//dprintf(2, "\nground: |%s|\n", j->command);
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	nanosleep(&tw, &tr);
}
