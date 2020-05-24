/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_zamena_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:19:10 by mbrella           #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static void		do_zam_slash_in_par(t_zams *zams, char *line, char c)
{
	ft_strcat_char(zams->dopstr, line[zams->i]);
	zams->i++;
	if (c == '\"')
	{
		while (line[zams->i] != '\0' && line[zams->i] != c)
		{
			if (line[zams->i] == '\\' && line[zams->i + 1] == '\"')
				ft_strcat_char(zams->dopstr, -1 * line[++zams->i]);
			else
				ft_strcat_char(zams->dopstr, line[zams->i]);
			zams->i++;
		}
	}
	else if (c == '\'')
	{
		while (line[zams->i] != '\0' && line[zams->i] != c)
		{
			ft_strcat_char(zams->dopstr, line[zams->i]);
			zams->i++;
		}
	}
	ft_strcat_char(zams->dopstr, line[zams->i]);
}

static void		decide_what_to_do(t_zams *zams, char *line)
{
	if (ispar(line[zams->i]))
	{
		do_zam_slash_in_par(zams, line, line[zams->i]);
	}
	else if (line[zams->i] == '\\' && line[zams->i + 1] != '\0')
	{
		ft_strcat_char(zams->dopstr, -1 * line[zams->i + 1]);
		zams->i++;
	}
	else
		ft_strcat_char(zams->dopstr, line[zams->i]);
}

int				do_zamena_slash(char *line, t_readline *p)
{
	t_zams	zams;

	zams.i = 0;
	if (line == NULL)
		return (-1);
	if (!(zams.dopstr = ft_memalloc(130000)))
		ft_error_q(2);
	while (zams.i < (int)ft_strlen(line) && line[zams.i] != '\0')
	{
		decide_what_to_do(&zams, line);
		zams.i++;
	}
	ft_strdel(&line);
	p->buff = zams.dopstr;
	p->len = ft_strlen(p->buff);
	return (p->len);
}
