/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:13:27 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/04 17:13:30 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_fork_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		signal(SIGINT, ft_fork_signal);
	}
}

int		ft_signal(int signo, t_readline *p)
{
	if (signo == 3)
	{
		free(p->buff);
		p->buff = ft_strnew(1);
		return (1);
	}
	else if (signo == 4)
	{
		if (p->buff[0] == '\0' || !p->buff[0] || p->index == 0)
		{
			free(p->buff);
			p->buff = ft_strdup("exit");
			return (1);
		}
		else
			return (4);
	}
	else if (signo == 26)
		return (27);
	else if (signo >= 0 && signo <= 30)
		return (42);
	return (404);
}
