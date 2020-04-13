/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_parser1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:19:33 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char			*do_zam_str_with_tilda(char *str)
{
	char	*hp;
	char	*tmp;

	if (*str == '\0')
		return (str);
	if (!(hp = ft_get_var("HOME", g_env)))
		return (NULL);
	if (ft_strstr(str, "~/") == str ||
			ft_strcmp("~", str) == 0)
	{
		tmp = str;
		str = ft_strjoin(hp, &str[1]);
		ft_strdel(&tmp);
	}
	ft_strdel(&hp);
	return (str);
}
