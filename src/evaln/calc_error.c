/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/04 13:41:58 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

t_int	*tmp_0(t_int *tmp, char *s)
{
	tmp->ol = 0;
	tmp->zl = 0;
	tmp->i = 0;
	tmp->d = 0;
	tmp->last_token = 0;
	tmp->s = s;
	return (tmp);
}

int		c_e(t_calce calce)
{
	if (calce.stackos != NULL)
		free(calce.stackos);
	if (calce.stackzn != NULL)
		free(calce.stackzn);
	if (calce.str != NULL)
		free(calce.str);
	ft_strdel(&calce.delstr);
	*calce.error = 1;
	return (-1);
}
