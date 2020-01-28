/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:59:15 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/27 16:59:17 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

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
	ft_memcpy(&tattr, &saved_attributes, sizeof(tattr));
	tattr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | ISIG | IEXTEN);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &tattr) == -1)
		return ;
}
