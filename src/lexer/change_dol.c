/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:25:17 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char				*do_zam_str_bax(char *str1, t_dop_str *t)
{
	int			i;
	int			dop;
	char		*dopstr;
	char		*str_for_del;

	i = 0;
	if (!(t->str_b = ft_strnew(130000)))
		ft_error_q(2);
	while (i < ft_strlen(str1) && str1[i] != '\0')
	{
		if (str1[i] == '$' && (str1[i + 1] != '('))
		{
			dop = (str1[i + 1] == '{' ? 2 : 1);
			dopstr = ft_strsub(str1, i + dop, word_size(&str1[i + 1]) - (dop == 2 ? 4 : 1) + 1);
			str_for_del = dopstr;
			dopstr = ft_get_var(dopstr, g_all_var);
			ft_strdel(&str_for_del);
			if (dopstr != NULL)
				ft_strcat(t->str_b, dopstr);
			i += word_size(&str1[i]);
			ft_strdel(&dopstr);
		}
		else
		{
			dopstr = ft_strdup(" ");
			dopstr[0] = str1[i];
			ft_strcat(t->str_b, dopstr);
			ft_strdel(&dopstr);
			i++;
		}
	}
	ft_strdel(&str1);
	return (t->str_b);
}
