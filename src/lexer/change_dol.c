/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:25:17 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 19:15:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

static void	zam_symbol(char *str1, t_zams *zams, t_dop_str *t)
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
			ft_strcat(t->str_b, zams->dopstr);
		zams->i += word_size(&str1[zams->i]);
		ft_strdel(&zams->dopstr);
	}
	else
	{
		zams->dopstr = ft_strdup(" ");
		zams->dopstr[0] = str1[zams->i];
		ft_strcat(t->str_b, zams->dopstr);
		ft_strdel(&zams->dopstr);
		zams->i++;
	}
}

char		*do_zam_str_bax(char *str1, t_dop_str *t)
{
	t_zams	zams;

	zams.i = 0;
	if (!(t->str_b = ft_strnew(130000)))
		ft_error_q(2);
	while (zams.i < (int)ft_strlen(str1) && str1[zams.i] != '\0')
		zam_symbol(str1, &zams, t);
	ft_strdel(&str1);
	return (t->str_b);
}
