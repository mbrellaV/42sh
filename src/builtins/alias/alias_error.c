/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/03 20:13:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

int			alias_error(int error, char *tmp1, char *tmp2)
{
	put_error_to_shell(error);
	if (error == 15)
	{
		ft_error(15, "parse error\n", NULL);
		return (-1);
	}
	if (error == 14)
	{
		vivod(2) ? ft_dprintf(globals()->fd[2],
				"alias [alias-name[=string]...]\n") : 0;
		return (-1);
	}
	vivod(2) ? ft_dprintf(globals()->fd[2],
			"alias error: wrong argument: |%s|\n", tmp2) : 0;
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (-1);
}
