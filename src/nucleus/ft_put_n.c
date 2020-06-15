/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:21:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int		ft_put_n(int len, int i, int max)
{
	struct winsize wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return (-1);
	if ((len + i) == wins.ws_col && i != max)
	{
		write(2, "\n", 1);
		return (1);
	}
	else
	{
		if (((len + i - wins.ws_col) % wins.ws_col) == 0 && i != max)
		{
			write(2, "\n", 1);
			return (1);
		}
	}
	return (-1);
}
