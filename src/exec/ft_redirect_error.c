/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	ft_redirect_error(int marker, char *dopline)
{
	put_error_to_shell(2);
	if (marker == 10)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: Bad file descriptor\n",
				dopline);
		ft_strdel(&dopline);
	}
	if (marker == 9)
	{
		ft_dprintf(globals()->fd[2], SHELL_NAME": %s: ambiguous redirect\n",
				dopline);
	}
}
