/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_flag_in_builtins.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		ft_open_flag_in_builtins(char *opt, int flag, int *infile, int *outfile)
{
	if (flag == 1 || flag == 2 || flag == 6)
		*outfile = open(opt, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else if (flag == 3)
		*infile = open(opt, O_RDONLY);
	if (((flag == 1 || flag == 6 || flag == 2) && *outfile <= 0) ||
		(flag == 3 && *infile <= 0))
	{
		ft_putstr_fd("42sh: open fd ERROR ", globals()->fd[2]);
		ft_putendl_fd(opt, globals()->fd[2]);
		return (-1);
	}
	return (1);
}
