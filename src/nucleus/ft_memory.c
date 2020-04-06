/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:49:45 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 16:49:46 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

t_memory	*ft_memory(t_memory *back, char **str)
{
	t_memory	*tmp;
	t_memory	*p;
	char		*dopstr;

	g_his_d = 0;
	dopstr = ft_strdup(*str);
	tmp = ft_memalloc(sizeof(t_memory));
	if (!tmp)
		return (NULL);
	p = back->next;
	back->next = tmp;
	//tmp->inp = dopstr;
	tmp->inp = do_zam_str_hist_var(*str, back);
	tmp->inp = do_reverse_zamena(tmp->inp);
	//ft_strdel(str);
	*str = dopstr;
	tmp->next = p;
	tmp->back = back;
	if (p != NULL)
		p->back = tmp;
	return (tmp);
}
