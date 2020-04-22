/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:49:45 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
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
	tmp = ft_memalloc(sizeof(t_memory));
	if (!tmp)
		return (NULL);
	p = back->next;
	back->next = tmp;
	tmp->inp = dopstr;
	*str = ft_strdup(tmp->inp);
	tmp->inp = do_reverse_zamena(tmp->inp);
	ft_strdel(&str_for_del);
	tmp->next = p;
	tmp->back = back;
	if (p != NULL)
		p->back = tmp;
	return (tmp);
}
