/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 18:29:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/fshell.h"

void		ft_alias(void)
{
	if (!(globals()->g_alias = (char **)ft_memalloc(4 * sizeof(char *))))
		ft_error(15, "malloc error alias", NULL);
	globals()->g_alias[0] = ft_strdup("ll=ls -la");
	globals()->g_alias[1] = ft_strdup("l=ls");
	globals()->g_alias[2] = NULL;
}

int			alias_dop(char *dop, char *prev_word, char *dopstr)
{
	ft_strdel(&prev_word);
	ft_strdel(&dopstr);
	ft_strdel(&dop);
	return (1);
}

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
