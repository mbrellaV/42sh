/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:54:56 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

void	do_hash(char **args)
{
	if (!args[1])
		print_hash();
	else if (args[2])
	{
		put_error_to_shell(2);
		ft_dprintf(globals()->fd[2], "42sh: hash: too many arguments!\nUsage: hash [-r]\n");
	}
	else if (args[1][0] != '-' || args[1][1] != 'r')
	{
		put_error_to_shell(2);
		ft_dprintf(globals()->fd[2], "42sh: hash: bad argument!\nUsage: hash [-r]\n");
	}
	else
		hash_clear();
}

void	print_hash(void)
{
	t_hash			*hash;
	int				i;

	i = -1;
	while (++i < MAX_HASH)
	{
		if (globals()->g_hash[i] != NULL)
		{
			hash = globals()->g_hash[i];
			while (hash)
			{
				ft_putstr_fd(hash->key, globals()->fd[1]);
				ft_putstr_fd("=", globals()->fd[1]);
				ft_putstr_fd(hash->value, globals()->fd[1]);
				if (hash->next)
					ft_putstr_fd("    ", globals()->fd[1]);
				hash = hash->next;
			}
			ft_putstr_fd("\n", globals()->fd[1]);
		}
	}
}
