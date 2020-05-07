/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:59:15 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

static void		norme_help(t_readline *p, char buf[8])
{
	if (p->sum_read == 27 || (p->sum_read == 119 && p->esc == 1))
		ft_do_copy(p);
	else if (ft_signal(p->sum_read, p) == 404)
		ft_do_addch(p, buf[0]);
	do_job_del();
}

int				ft_read_helper(t_readline *p, t_memory *h, int rt, char *buf)
{
	if (rt > 1)
		ft_cheak_sum(p, &h);
	else if (p->sum_read == 9)
		ft_cheak_tab(p);
	else if (p->sum_read == 18)
		ft_add_his(p, h);
	else if (p->sum_read == 25 || p->sum_read == 23 || p->sum_read == 21 ||
	p->sum_read == 127)
		ft_cut_copy(p);
	else if (ft_signal(p->sum_read, p) == 1)
		return (0);
	else
		norme_help(p, buf);
	return (1);
}

void			reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &saved_attributes);
}

void			error_term(int error)
{
	if (error == 1)
	{
		ft_putendl_fd("42sh: Not a terminal.\n", 2);
		exit(1);
	}
}

int				set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(0))
		return (1);
	if (tgetent(NULL, getenv("TERM")) < 1)
		error_term(1);
	if (tcgetattr(0, &saved_attributes) == -1)
		error_term(1);
	ft_memcpy(&tattr, &saved_attributes, sizeof(tattr));
	tattr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | ISIG | IEXTEN);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &tattr) == -1)
		error_term(1);
	atexit(reset_input_mode);
	return (0);
}
