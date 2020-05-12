/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 15:40:50 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

int			alias_error(int error, char *tmp1, char *tmp2)
{
	put_error_to_shell(error);
	if (error == 15)
	{
		ft_error(15, "parse error");
		return (-1);
	}
	if (error == 14)
	{
		ft_dprintf(globals()->fd[2], "alias [alias-name[=string]...]\n");
		return (-1);
	}
	ft_dprintf(globals()->fd[2], "alias error: wrong argument: |%s|\n", tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (-1);
}
