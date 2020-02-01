/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:23:56 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/04 13:24:00 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_hex(char *str)
{
	int	i;

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
	ft_putchar(i);
	return (str);
}

char	*ft_put_env(char *str)
{
	char	*tmp;
	int		k;
	char	*buf;
	int		len;

	str++;
	buf = ft_strjoin_cmp(str, ' ' & '\"');
	len = ft_strlen(buf);
	tmp = buf;
	buf = ft_strjoinch(tmp, '=');
	free(tmp);
	k = ft_findenv(buf, g_env);
	if (k != -404)
	{
		ft_putstr(&g_env[k][len + 1]);
	}
	str = str + len - 1;
	free(buf);
	return (str);
}

char	*ft_cd_home(char *str)
{
	char	*tmp;
	int		k;
	char	*buf;

	if (*(str + 1) != '/')
		tmp = ft_strjoin("/", (str + 1));
	k = ft_findenv("HOME=", g_env);
	if (k != -404)
	{
		buf = tmp;
		tmp = ft_strjoin(&g_env[k][5], buf);
		free(buf);
	}
	return (tmp);
}
