/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_tkn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 15:40:48 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkn	*calc_newtkn(char *value, t_calc_tkntype type)
{
	t_calc_tkn	*token;

	if (!(token = (t_calc_tkn *)ft_memalloc(sizeof(t_calc_tkn))))
		return (NULL);
	token->value = value;
	token->type = type;
	token->start_pos = 0;
	token->end_pos = 0;
	return (token);
}

void		calc_del_tkn(t_calc_tkn **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->value)
		ft_memdel((void **)&(*token)->value);
	(*token)->type = 0;
	free(*token);
	*token = NULL;
}
