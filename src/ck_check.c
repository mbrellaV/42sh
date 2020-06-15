/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

static int			norme_help(int f, char **buff)
{
	ft_dprintf(globals()->fd[2], f == -1 ? SY_E_1 : SY_E_2);
	free(*buff);
	return (1);
}

int					ft_ck_addline(t_readline *p)
{
	int				f;
	t_memory		*dop_memory;

	f = 4242;
	while (f != 1)
	{
		if (p->buff[0] != '\0')
		{
			if (!(dop_memory = ft_add_to_history(globals()->g_memory_head,
					&(p->buff))) && strdelr(&p->buff))
				return (-1);
			globals()->g_memory_head = dop_memory;
		}
		p->index = ft_do_zam_alias(&p->buff);
		while (p->index > 0 && p->buff[p->index - 1] == '\\' &&
				!(p->buff[p->index - 1] = 0))
			ft_add_intput_que(p, globals()->g_memory_head, 11);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, globals()->g_memory_head, 1);
		if ((f = ck_br(p->buff)) == 0)
			ft_add_intput_que(p, globals()->g_memory_head, 20);
		else if ((f == -1 || f == -2) && norme_help(f, &p->buff))
			return (0);
	}
	return (1);
}

char				*ck_br_faf(char *s)
{
	int				i;
	char			c;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			s[i] = 'F';
			while (s[++i] != c)
				s[i] = 'a';
			s[i] = 'F';
		}
	}
	return (s);
}

char				*ck_br_cycle(char *s, int k, int i)
{
	while (1)
	{
		i = -1;
		while (s[++i])
			if (s[i] == '(')
				k = i;
		if (s[k] && s[k] == '(')
		{
			i = k;
			while (s[++i] && s[i] != ')')
				;
		}
		else
			break ;
		if (s[i] && s[i] == ')')
		{
			s[k] = 'A';
			s[i] = 'A';
		}
		else if (strdelr(&s))
			return (NULL);
	}
	return (s);
}

int					ck_br(const char *str)
{
	char			*s;
	int				i;
	int				k;

	k = 0;
	s = ft_strdup(str);
	s = ck_br_faf(s);
	if ((i = check_bracket(s)) && i != 1 && strdelr(&s))
		return (i);
	if ((s = ck_br_cycle(s, k, i)) == NULL)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return (1);
}
