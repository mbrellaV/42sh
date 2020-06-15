/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_quest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 20:21:00 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int			do_quest(int wait_and, int wait_or)
{
	char	*del;
	int		num;

	if (!(del = ft_get_var("?", globals()->g_all_var)))
	{
		put_error_to_shell(2);
		return (1);
	}
	num = ft_atoi(del);
	ft_strdel(&del);
	if ((wait_and == 1 && num > 0) || (wait_or == 1 && num == 0))
	{
		return (1);
	}
	return (0);
}
