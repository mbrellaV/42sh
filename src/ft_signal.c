/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:13:27 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	recover_normal_shell_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

void	disable_shell_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void	ft_fork_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", globals()->all_opened_fds[2]);
		signal(SIGINT, ft_fork_signal);
	}
	else if (signo == SIGTSTP)
		;
	else if (signo == SIGSTOP)
	{
		printf("TRUE\n");
		signal(SIGSTOP, SIG_IGN);
	}
	else if (signo == SIGCONT)
		;
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
			return (ft_error_d(p));
		else
			return (4);
	}
	else if (signo == 26)
		return (27);
	else if (signo >= 0 && signo <= 30)
		return (42);
	return (404);
}
