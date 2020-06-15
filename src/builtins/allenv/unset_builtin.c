/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:19:45 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			unset_builtin(char **file_args)
{
	int		i;

	i = 0;
	if (file_args == NULL)
		return (vivod(2) ? (ft_dprintf(globals()->fd[2],
				"an error ocured\n")) : 1);
	else if (file_args[1] != NULL)
	{
		while (file_args[i])
		{
			unset_var(file_args[i], &globals()->g_env);
			unset_var(file_args[i], &globals()->g_all_var);
			i++;
		}
	}
	return (0);
}
