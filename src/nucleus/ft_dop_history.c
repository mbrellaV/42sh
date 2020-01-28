/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dop_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:07 by qmartina          #+#    #+#             */
/*   Updated: 2020/01/28 16:52:08 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void		ft_dop_history(t_memory ***q, char ***input, t_flag **flag, int k)
{
	if (k == 1)
	{
		free(**input);
		**input = ft_strdup((**q)->inp);
		ft_cleanstr((*flag)->i);
		(*flag)->i = ft_strlen(**input);
		(*flag)->max = ft_strlen(**input);
		ft_putstr_fd((**q)->inp, 2);
	}
	else if (k == 2)
	{
		free(**input);
		**input = ft_strnew(1);
		ft_cleanstr((*flag)->i);
		(*flag)->i = ft_strlen(**input);
		(*flag)->max = ft_strlen(**input);
		ft_putstr_fd(**input, 2);
	}
}
