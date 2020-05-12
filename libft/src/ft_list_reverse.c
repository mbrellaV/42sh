/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:27:08 by qmartina          #+#    #+#             */
/*   Updated: 2020/05/12 15:40:49 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_list *begin_list)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	if (begin_list)
	{
		a = begin_list;
		while (a)
		{
			b = a->next;
			a->next = c;
			c = a;
			a = b;
		}
		begin_list = c;
	}
	else
		return ;
}
