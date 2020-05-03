/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:53:55 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_printf.h"
#include <math.h>
#include <limits.h>

int	main(void)
{
	char s[1000];
	char *str;

	ft_bzero(s, 1000);
	ft_dprintf(globals()->all_opened_fds[1], "test:\n");
	ft_dprintf(globals()->all_opened_fds[1], "*TEST*%d***\n",
			ft_dprintf(globals()->all_opened_fds[1],
					"{RED}%#08.3o{EOC}", 8375));
	ft_dprintf(globals()->all_opened_fds[1], "\n");
	ft_dprintf(globals()->all_opened_fds[1], "orig:\n");
	ft_dprintf(globals()->all_opened_fds[1], "*ORIG*%d***\n",
			printf("{RED}%#08.3o{EOC}", 8375));
	ft_strprintf(&str, "{RED}%#08.3o{EOC}", 8375);
	ft_dprintf(globals()->all_opened_fds[1], "TEST StrPRINT: %s\n", str);
	sprintf(s, "{RED}%#08.3o{EOC}", 8375);
	ft_dprintf(globals()->all_opened_fds[1], "ORTEST SPRINT: %s\n", s);
	return (6);
}
