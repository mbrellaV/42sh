/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errror_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:12:39 by qmartina          #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			ft_error(int error, char *dopline, char *str_to_del)
{
	put_error_to_shell(2);
	if (error == 5)
	{
		ft_dprintf(globals()->fd[2],
				"parse error near: %s\n", dopline);
	}
	if (str_to_del != NULL)
		ft_strdel(&dopline);
	return (-1);
}
