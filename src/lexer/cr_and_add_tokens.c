/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_and_add_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:43:37 by mbrella           #+#    #+#             */
/*   Updated: 2020/06/15 23:31:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

t_lextoken		*ft_cr_new_token(char *line, int op_type)
{
	t_lextoken	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_lextoken))))
		ft_error_q(2);
	tmp->next = NULL;
	tmp->line = line;
	tmp->operator_type = op_type;
	tmp->is_near_opt = 0;
	tmp->is_near_word = 0;
	return (tmp);
}

t_lextoken		*add_token(t_lextoken *start, char *line)
{
	t_lextoken	*tmp;

	if (start == NULL)
	{
		tmp = ft_cr_new_token(line, get_op_type(line));
		tmp->prev = NULL;
		return (tmp);
	}
	tmp = start;
	while (tmp->next != NULL)
		tmp = tmp->next;
	start = tmp;
	tmp = ft_cr_new_token(line, get_op_type(line));
	start->next = tmp;
	tmp->prev = start;
	return (tmp);
}
