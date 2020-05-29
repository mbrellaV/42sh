/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:25:17 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void	zam_symbol(char *str1, t_zams *zams, char *new)
{
	if (str1[zams->i] == '$' && (str1[zams->i + 1] != '('))
	{
		zams->dop = (str1[zams->i + 1] == '{' ? 2 : 1);
		zams->dopstr = ft_strsub(str1, zams->i + zams->dop,
			word_size(&str1[zams->i]) - (zams->dop == 2 ? 4 : 1) + 1);
		zams->str_for_del = zams->dopstr;
		zams->dopstr = ft_get_var(zams->dopstr, globals()->g_all_var);
		ft_strdel(&zams->str_for_del);
		if (zams->dopstr != NULL)
			ft_strcat(new, zams->dopstr);
		zams->i += word_size(&str1[zams->i]);
		ft_strdel(&zams->dopstr);
	}
	else
	{
		zams->dopstr = ft_strdup(" ");
		zams->dopstr[0] = str1[zams->i];
		ft_strcat(new, zams->dopstr);
		ft_strdel(&zams->dopstr);
		zams->i++;
	}
}

char		*do_zam_str_bax(char *str1)
{
	t_zams	zams;
	char	*new;
	char 	*dop;

	zams.i = 0;
	if (!(new = ft_strnew(130000)))
		ft_error_q(2);
	while (zams.i < (int)ft_strlen(str1) && str1[zams.i] != '\0')
	{
		if (str1[zams.i] == '\'')
		{
			dop = ft_strsub(str1, zams.i, c_size(&str1[zams.i], str1[zams.i]) + 2);
			ft_strcat(new, dop);
			zams.i += c_size(&str1[zams.i], str1[zams.i]) + 2;
			ft_strdel(&dop);
		}
		zam_symbol(str1, &zams, new);
	}
	ft_strdel(&str1);
	return (new);
}
