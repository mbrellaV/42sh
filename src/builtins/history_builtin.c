/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:15:45 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		hist_builtin(char **mas)
{
	if (mas[0] != NULL && mas[1] == NULL)
		show_history(globals()->g_memory_head);
	else if (mas[0] != NULL && mas[1] != NULL && mas[2] == NULL)
	{
		if (!ft_strcmp(mas[1], "clear"))
		{
			del_hist();
			return (0);
		}
	}
	return (0);
}
