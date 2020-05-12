/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errror_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:12:39 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int			ft_error(int error, char *dopline)
{
	put_error_to_shell(2);
	if (error == 5)
	{
		ft_dprintf(globals()->fd[2],
				"parse error near: %s\n", dopline);
	}
	return (-1);
}
