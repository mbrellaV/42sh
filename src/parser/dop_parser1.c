/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_parser1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:19:33 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/16 16:19:34 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char			*dop_zam_str(char *str, char *new, char *hp)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
		{
			ft_strcat(new, hp);
			i += ft_strlen(hp);
		}
		else if (str[i] == '\\')
		{
			if (str[i + 1] == '~')
			{
				ft_strcat(new, "~");
				i += ft_strlen("~");
			}
		}
		else
			new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char			*do_zam_str(char *str)
{
	int		i;
	char	*hp;
	char	*new;
	int		c;

	c = 0;
	if (!(hp = ft_get_var("HOME", g_env)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
			c++;
		i++;
	}
	if (!(new = ft_memalloc((ft_strlen(hp) * c) + ft_strlen(str) + 1)))
		return (NULL);
	if (!(dop_zam_str(str, new, hp)))
		return (NULL);
	ft_strdel(&hp);
	ft_strdel(&str);
	return (new);
}
