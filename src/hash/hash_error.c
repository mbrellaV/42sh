/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:48:50 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*hash_error(int err, char *key, int no_error)
{
	if (no_error)
		return (NULL);
	put_error_to_shell(2);
	if (err == 1)
	{
		ft_dprintf(globals()->all_opened_fds[2], "42sh: no such file or directory: '%s'\n", key);
		return (NULL);
	}
	else if (err == 2)
	{
		ft_dprintf(globals()->all_opened_fds[2], SHELL_NAME": command not found: '%s'\n", key);
		return (NULL);
	}
	else if (err == 3)
	{
		ft_dprintf(globals()->all_opened_fds[2], "42sh: permission denied: |%s|\n", key);
		return (NULL);
	}
	return (NULL);
}
