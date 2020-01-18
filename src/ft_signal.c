/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:13:27 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/04 17:13:30 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_fork_signal(int signo)
{
	exit(0);
	if (signo == SIGINT)
	{

		ft_putstr_fd("\n", 2);
		signal(SIGINT, ft_fork_signal);
	}
}

int		ft_signal(int signo, char **input)
{
	if (signo == 3)
	{
		free(*input);
		*input = ft_strnew(1);
		return (1);
	}
	else if (signo == 4)
	{
		if (*input[0] == '\0')
		{
			free(*input);
			*input = ft_strdup("exit");
			return (1);
		}
		else
			return (4);
	}
	else if (signo == 26 || signo == 9)
		return (27);
	return (404);
}


