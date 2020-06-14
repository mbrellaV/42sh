/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:13:27 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 00:13:27 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int					do_42sh_builtin(char **av)
{
	int				fd;
	char			*command;

	if (av[0] && av[1] && av[2] == NULL)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
			return (err_fc("42sh read error!\n"));
		command = read_fc(fd);
		if (launch(command, 1))
			return (1);
		free(command);
		return (0);
	}
	ft_dprintf(globals()->fd[2], "parse error\n");
	return (1);
}
