/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plettie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:05:01 by plettie           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_hex(char *str)
{
	int		i;

	i = 0;
	str++;
	if (*str >= '0' && *str <= '9')
	{
		i += (*str - '0');
		str++;
	}
	else if ((*str >= 'A' && *str <= 'F') || (*str >= 'a' && *str <= 'f'))
	{
		i += (*str - 'A' + 10);
		str++;
	}
	else
		str--;
	if (*str >= '0' && *str <= '9')
		i = (i * 16) + (*str - '0');
	else if ((*str >= 'A' && *str <= 'F') || (*str >= 'a' && *str <= 'f'))
		i = (i * 16) + (*str - 'A' + 10);
	else
		str--;
	str++;
	ft_dprintf(globals()->fd[1], "%d", i);
	return (str);
}

char	*ft_flag_echo(char *str, t_builtins *echo)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (str);
	}
	echo->echo_n = 1;
	return (str + i);
}

char	*distribute_echo(char **str, int k, int flag, t_builtins *echo)
{
	while (str[k] && *str[k])
	{
		if (*str[k] == '\\' && (flag = 1))
			str[k] = ft_slash(str[k], echo);
		else if (*str[k] == '-' && flag == 0)
			str[k] = ft_flag_echo(str[k], echo);
		else if ((flag = 1))
		{
			ft_putchar_fd(*str[k], globals()->fd[1]);
			str[k]++;
		}
	}
	return (str[k]);
}
