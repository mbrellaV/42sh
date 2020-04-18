/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:48:50 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
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
		ft_printf("21sh: no such file or directory: '%s'\n", key);
		return (NULL);
	}
	else if (err == 2)
	{
		ft_printf(SHELL_NAME" command not found: '%s'\n", key);
		return (NULL);
	}
	else if (err == 3)
	{
		ft_printf("21sh: permission denied: |%s|\n", key);
		return (NULL);
	}
	return (NULL);
}
