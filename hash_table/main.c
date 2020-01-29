/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:16:04 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/28 17:16:05 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>
#include <readline/readline.h>

void				print_hash()
{
	t_hash			*hash;
	int				i;

	i = -1;
	while (++i < MAX_HASH)
	{
		if (g_hash[i])
		{
			hash = g_hash[i];
			while (hash)
			{
				printf("hash - [%i]; key - [%s];  value - [%s]    ", str_to_hash(hash->key), hash->key, hash->value);
				hash = hash->next;
			}
			printf("\n");
		}
	}
}

int					main()
{
	char			*line;
	char			*hash;

	hash_init();
	while ((line = readline("")))
	{
		if (!ft_strcmp(line, "print"))
			print_hash();
		else if (!ft_strcmp(line, "clear"))
			hash_clear();
		else
		{
			hash = hash_get(line);
			printf("%s\n", hash ? hash : "Command not found");
		}
		free(line);
	}
	return 0;
}
