/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str_by_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:42:50 by mbrella           #+#    #+#             */
/*   Updated: 2020/01/27 13:42:51 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char				*str_by_str2(int start, int end, char *zam_str, char *str)
{
	int		i;
	int		dopi;
	char	*newstr;

	i = 0;
	dopi = 0;
	if (!(newstr = ft_memalloc((ft_strlen(str) +
			ft_strlen(zam_str) + 2) * sizeof(char))))
		ft_error_q(2);
	while (str[i] != '\0' && i < start - 1)
	{
		newstr[i] = str[i];
		i++;
	}
	while (zam_str[dopi] != '\0')
		newstr[i++] = zam_str[dopi++];
	while (str[end] != '\0')
		newstr[i++] = str[end++];
	ft_strdel(&str);
	ft_strdel(&zam_str);
	return (newstr);
}

char				*do_zam_str_by_str(int start, int end, char *str,
		char *zam_str)
{
	if (str == NULL)
	{
		ft_strdel(&str);
		ft_strdel(&zam_str);
		return ((char *)ft_memalloc(130000));
	}
	if (zam_str == NULL)
		zam_str = ft_strdup("\0");
	return (str_by_str2(start, end, zam_str, str));
}
