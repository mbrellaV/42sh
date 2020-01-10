/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:24:30 by qmartina          #+#    #+#             */
/*   Updated: 2019/12/05 18:24:32 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		ft_c(int c)
{
	write(2, &c, 1);
	return (1);
}

void	reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &saved_attributes);
}

void	set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(0))
	{
		ft_putendl_fd("Not a terminal.\n", 2);
		exit(1);
	}
	if (tgetent(NULL, getenv("TERM")) < 1)
		return ;
	if (tcgetattr(0, &saved_attributes) == -1)
		return ;
	memcpy(&tattr, &saved_attributes, sizeof(tattr));
	tattr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | ISIG | IEXTEN);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &tattr) == -1)
		return ;
}

void	ft_setcursor(int i, int max)
{
	while (max > i)
	{
		write(2, "\b", 1);
		max--;
	}
}

void	set_input_mode_t(void)
{
	struct termios tattr;

	if (!isatty(0))
	{
		ft_putendl_fd("Not a terminal.\n", 2);
		exit(1);
	}
	if (tgetent(NULL, getenv("TERM")) < 1)
		return ;
	memcpy(&tattr, &saved_attributes, sizeof(tattr));
	tattr.c_cc[VEOF] = 81;
	if (tcsetattr(0, 0, &tattr) == -1)
		return ;
}
