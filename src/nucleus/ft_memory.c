/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:49:45 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/02 13:20:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

t_memory	*ft_memory(t_memory *back, char **str)
{
	t_memory	*tmp;
	t_memory	*p;
	char		*str_for_del;
	char		*dopstr;

	globals()->g_his_d = 0;
	str_for_del = ft_strdup(*str);
	if (!(dopstr = do_zam_str_hist_var(*str, back)))
	{
		ft_strdel(&str_for_del);
		return (NULL);
	}
	if (!(tmp = ft_memalloc(sizeof(t_memory))))
		return (NULL);
	if (!(tmp->inp = ft_memalloc(130000)))
		return (NULL);
	ft_strcat(tmp->inp, dopstr);
	ft_strdel(&dopstr);
	p = back->next;
	back->next = tmp;
	*str = ft_strdup(tmp->inp);
	tmp->inp = do_reverse_zamena(tmp->inp);
	ft_strdel(&str_for_del);
	tmp->next = p;
	tmp->back = back;
	if (p != NULL)
		p->back = tmp;
	return (tmp);
}
