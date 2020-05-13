/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_arr_reloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 22:36:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_calc_tkns	*calc_reloc_tkns(t_calc_tkns *s_tokens)
{
	t_calc_tkn		*new_tokens;

	if (!s_tokens)
		return (NULL);
	if (!(new_tokens = (t_calc_tkn *)ft_memalloc(sizeof(t_calc_tkn)
		* (s_tokens->malloc_size + CALC_TOKENS_SIZE))))
		return (s_tokens);
	new_tokens = ft_memcpy(new_tokens, s_tokens->tokens, sizeof(t_calc_tkn)
		* s_tokens->malloc_size);
	free(s_tokens->tokens);
	s_tokens->tokens = new_tokens;
	s_tokens->malloc_size += CALC_TOKENS_SIZE;
	return (s_tokens);
}
