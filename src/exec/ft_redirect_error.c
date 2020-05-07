/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 13:53:14 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	ft_redirect_error(int marker, char *dopline)
{
	put_error_to_shell(2);
	if (marker == 10)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: Bad file descriptor",
				dopline);
		ft_strdel(&dopline);
	}
	if (marker == 9)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: ambiguous redirect",
				dopline);
	}
}
