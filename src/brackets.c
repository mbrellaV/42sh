/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/15 16:17:33 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int	ck_br(const char *str)
{
	char	*s;
	int		i;
	int		k = 0;
	char	c;

	s = ft_strdup(str);
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
	if ((i = check_bracket(s)) && i != 1)
	{
		ft_strdel(&s);
		return (i);
	}
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
		else
		{
			ft_strdel(&s);
			return (0);
		}
	}
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return(1);
}

int			ft_ck_addline(t_readline *p)
{
	int		f;

	f = 4242;
	while (f != 1)
	{
		p->index = do_zamena_slash(p->buff, p);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, g_memory_head, 1);
		p->index = do_zamena_slash(p->buff, p);
		while (p->index > 0 && p->buff[p->index - 1] == '\\')
		{
			p->buff[p->index - 1] = 0;
			ft_add_intput_que(p, g_memory_head, 11);
		}
		p->index = do_zamena_slash(p->buff, p);
		if ((f = ck_br(p->buff)) == 0)
			ft_add_intput_que(p, g_memory_head, 20);
		else if (f == -1 || f == -2)
		{
			ft_putstr_fd("Error \"()\"\n", 2);
			free(p->buff);
			return (0);
		}
	}
	return (1);
}
