/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errror_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:12:39 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int			ft_error(int error, char *dopline)
{
	if (error == 5)
	{
		ft_printf("parse error near: %s\n", dopline);
	}
	return (-1);
}
